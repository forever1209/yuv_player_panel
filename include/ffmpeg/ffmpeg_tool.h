extern "C" {
#include "libavutil/imgutils.h"
#include "libswscale/swscale.h"
#include "libavutil/frame.h"
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
        };
    } // namespace video
    
} // namespace mc
