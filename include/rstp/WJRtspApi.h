//
// Created by liulei on 2023/4/14.
//

#ifndef RTSPDEMOEXE_WJRTSPAPI_H
#define RTSPDEMOEXE_WJRTSPAPI_H
#include <stdint.h>
#ifdef  __cplusplus
extern "C"
{
#endif

typedef enum
{
    I_FRAME = 1,	//I帧
    P_FRAME ,	//P帧
    SPS_FRAME ,	//SPS帧
    PPS_FRAME ,	//PPS帧
    VPS_FRAME ,	//VPS帧， H265才有
    INVALID_FRAME,
}FrameType;

typedef struct  frameInfo
{
    uint8_t*   framebuffer;	//视频帧的起始地址
    uint32_t  size;				//视频帧长度
    FrameType  type;	//码流帧类型
    long capture_sec_time; //视频帧对应的曝光时间--秒
    long capture_msec_time; //视频帧对应的曝光时间--毫秒
    long recv_sec_time;		//接收到该帧时间--秒_部分
    long recv_msec_time;	//接收到该帧时间--毫秒_部分

}FrameInfo;
typedef void* WJRtspHandle;
typedef void* ClientHandle;
typedef void(*ClientCallback)(ClientHandle handle,FrameInfo  info);
/**
 * 创建连接句柄
 * @return wjrtsphandle
 */
WJRtspHandle RtspClientCreate();
/**
 * 回调方式创建拉流句柄
 * @param handle 客户端句柄
 * @param cb 回调函数
 * @return wjrtsphandle
 */
WJRtspHandle RtspClientCbCreate(ClientHandle handle,ClientCallback cb);
/**
 * rtsp客户端打开网络串流
 * @param handle  连接句柄
 * @param url   rtsp拉流地址
 * @return 0：filed 1：success
 */
int  RTSPClientOpenStream(WJRtspHandle  handle,  char* url);
/**
 * 注册回调函数
 * @param l_pRtspHandle wjrtsphandle
 * @param l_pClientHandle 客户端句柄
 * @param cb 回调函数
 * @return 0：filed 1：success
 */
int ReginstCallBack(WJRtspHandle  l_pRtspHandle, ClientHandle l_pClientHandle,ClientCallback cb);
/**
 *
 * @param handle
 * @return 0：filed 1：success
 */
int  RTSPClientCloseStream(WJRtspHandle  handle);
/**
 *
 * @param handle
 */
void  RTSPClientDestroy(WJRtspHandle  handle);

const  char* GetApiVersion();

#ifdef  __cplusplus
}
#endif



#endif //RTSPDEMOEXE_WJRTSPAPI_H
