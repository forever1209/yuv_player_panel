extern "C" {
#include "libavutil/imgutils.h"
#include "libswscale/swscale.h"
#include "libavutil/frame.h"
#include "libavcodec/avcodec.h"
}

namespace mc
{
    namespace video
    {
        class FFmpegTool
        {
        public:
            FFmpegTool();
            ~FFmpegTool();
        public:
            void InitDecoder();
            static void ConvertYUYVtoYUV(unsigned char* yuyvData, AVFrame  *frmyuyv,int width, int height) ;
            AVFrame* DecodeOneFrame(const uint8_t* data,const  int &size);
        private:
            AVCodec* codec;
            AVCodecContext* codecContext;
            AVFrame* frame;
            bool m_bInit = false;
        };
    } // namespace video
    
} // namespace mc
