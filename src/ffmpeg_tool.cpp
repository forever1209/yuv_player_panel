#include "ffmpeg/ffmpeg_tool.h"
#include "ffmpeg_tool.h"
namespace mc
{
    namespace video
    {
        FFmpegTool::FFmpegTool()
        {
            
        }
        FFmpegTool::~FFmpegTool()
        {
        }
        void FFmpegTool::InitDecoder()
        {
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
            return nullptr;
        }
    } // namespace video

} // namespace mc
