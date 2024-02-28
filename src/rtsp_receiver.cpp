#include "rstp/rtsp_receiver.h"
namespace mc
{
    namespace rtsp
    {
        static void MyCallBack(ClientHandle handle,FrameInfo  info)
        {
            // if(auto ptr = static_cast<mc::rtsp::RtspReceiver*>(handle))
            // {
            //     std::cout<<"change success"<<std::endl;
            //     ptr->DataPop(info.framebuffer,info.size);
            // }
            std::cout<<"call back"<<info.type<<"----"<<info.capture_sec_time<<" , size "<<info.size<<std::endl;
        }
        RtspReceiver::RtspReceiver()
        {
            m_strUrl = "";
        }
        RtspReceiver::~RtspReceiver()
        {
            if(l_rtspH)
            {
                Close();
            }
        }
        void RtspReceiver::Init(const std::string &url)
        {
            m_strUrl = url;
        }
        bool RtspReceiver::OpenAndCb(CallBack cb, void *ptr)
        {
            m_cb = cb;
            clinetPtr = ptr;
            if(l_rtspH==nullptr)
            {
                l_rtspH = RtspClientCreate();
                ReginstCallBack(l_rtspH, nullptr,MyCallBack);
                RTSPClientOpenStream(l_rtspH, (char*)m_strUrl.c_str());
            }
            else
            {
                Close();
            }
            return true;
        }
        void RtspReceiver::DataPop(uint8_t *data, const uint32_t &len)
        {
        }
        void RtspReceiver::Close()
        {
            RTSPClientCloseStream(l_rtspH);
            RTSPClientDestroy(l_rtspH);
        }
    }
}

