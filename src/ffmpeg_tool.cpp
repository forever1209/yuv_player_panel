#include "ffmpeg/ffmpeg_tool.h"
#include <iostream>
namespace mc
{
    namespace video
    {
        FFmpegTool::FFmpegTool()
        {
            m_bInit = false;
        }
        FFmpegTool::~FFmpegTool()
        {
            if(m_bInit)
            {
                avcodec_free_context(&codecContext);
                av_frame_free(&frame);
            }           
        }
        void FFmpegTool::InitDecoder()
        {
            codec = avcodec_find_decoder(AV_CODEC_ID_H264);
            codecContext = avcodec_alloc_context3(codec);
            avcodec_open2(codecContext, codec, nullptr);
            frame = av_frame_alloc();
            m_bInit= true;
        }
        void FFmpegTool::ConvertYUYVtoYUV(unsigned char *yuyvData, AVFrame *frm420p, int width, int height)
        {
            AVFrame  *frmyuyv = av_frame_alloc();
            av_image_fill_arrays(frmyuyv->data, frmyuyv->linesize, (uint8_t*)yuyvData, AV_PIX_FMT_YUYV422, width, height, 16);

            frm420p->width = width;
            frm420p->height = height;
            frm420p->format = AV_PIX_FMT_YUV420P;

            int ySize = width * height;
            int uvSize = ySize / 4;

            // frm420p->data[0] = yData;
            // frm420p->data[1] = uData;
            // frm420p->data[2] = vData;

            // frm420p->linesize[0] = width;
            // frm420p->linesize[1] = width / 2;
            // frm420p->linesize[2] = width / 2;

            struct SwsContext *sws = sws_getContext(width, height, AV_PIX_FMT_YUYV422, width, height, AV_PIX_FMT_YUV420P,
                                                    SWS_BILINEAR, NULL, NULL, NULL);

            int ret = sws_scale(sws, frmyuyv->data, frmyuyv->linesize, 0, height, frm420p->data, frm420p->linesize);

            //emit signalUpdate(frm420p->data[0],frm420p->data[1],frm420p->data[2],frm420p->linesize[0],frm420p->linesize[1],frm420p->linesize[2]);
            av_frame_free(&frmyuyv);
            av_frame_free(&frm420p);
            sws_freeContext(sws);
        }
        AVFrame *FFmpegTool::DecodeOneFrame(const uint8_t *data, const int &size)
        {
            AVPacket *packet = av_packet_alloc();
            packet->data = const_cast<uint8_t*>(data);
            packet->size = size;

            int response = avcodec_send_packet(codecContext, packet);
            if (response < 0) {
                std::cerr << "无法发送视频包给解码器" << std::endl;
                av_packet_free(&packet); // 释放 AVPacket 内存
                return nullptr;
            }

            response = avcodec_receive_frame(codecContext, frame);
            if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
                av_packet_free(&packet); // 释放 AVPacket 内存
                return nullptr;
            }
            else if (response < 0) {
                std::cerr << "无法从解码器接收视频帧" << std::endl;
                av_packet_free(&packet); // 释放 AVPacket 内存
                return nullptr;
            }

            // 处理视频帧数据，这里简单打印宽高信息
            std::cout << "解码得到视频帧，宽度：" << frame->width << "，高度：" << frame->height << std::endl;

            av_packet_free(&packet); // 释放 AVPacket 内存
            return frame;
        }
    } // namespace video

} // namespace mc
