#ifndef MCRTSP_RECEIVER_H
#define MCRTSP_RECEIVER_H
#include "WJRtspApi.h"
#include <iostream>
#include <memory>
#include <thread>
typedef void (*CallBack)(uint8_t *yData,uint8_t * uData,uint8_t *vData,const int &ySize,const int &uSize,const int &vSize,void *ptr);
namespace mc
{
    namespace video
    {
        class FFmpegTool;
    }
    namespace rtsp
    {
        class RtspReceiver
        {
        public:
            RtspReceiver();
            ~RtspReceiver();
        public:
            void Init(const std::string & url);
            bool OpenAndCb(CallBack cb,void *ptr);
            void DataPop(uint8_t * data,const uint32_t &len);
        private:
            void Close();
            void ThreadOpen();
        private:
            WJRtspHandle l_rtspH = nullptr;
            std::string m_strUrl = "";
            CallBack m_cb=nullptr;
            void * clinetPtr = nullptr;
            std::unique_ptr<std::thread> m_pthRead = nullptr;
            mc::video::FFmpegTool * m_pFmpegTool = nullptr;
        };
    }
}

#endif //MCRTSP_RECEIVER_H