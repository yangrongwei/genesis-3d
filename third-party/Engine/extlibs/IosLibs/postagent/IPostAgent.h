/**
 * @file IPostAgent.h
 * @brief POSTAGENT实现类，封装POST的操作给外部MODULE调用
 * @author cuikehong
 * @version 1.0.0
 * @date 2012-05-08
 */

#ifndef _IPOSTAGENT_H_
#define _IPOSTAGENT_H_

#if defined(__POST_AGENT_DLLEXPORT__)
#   if defined(PostAgent_EXPORTS)
#      define POSTAGENT_API __declspec(dllexport)
#   else 
#      define POSTAGENT_API __declspec(dllimport)
#   endif 
#else 
#   define POSTAGENT_API 
#endif 

namespace platform 
{

namespace founder 
{
    class Packet;
}

namespace postagent 
{

using namespace founder;

typedef unsigned int ChannelID_t;
#define INVALID_CHANNELID ((ChannelID_t)-1)

#define MAX_SERVER_NAME 64


enum ERRORCODE
{
    LOGIN_SUCCESS               = 0,//登录成功
    LOGIN_CONNECT_FAIL          = -1,//连接POST失败
    LOGIN_POST_DISCONNECT       = -1,//POST断开连接
    LOGIN_POST_KEY_ERROR        = -2,//KEY验证错误
    CHANNEL_CREATE_ERROR        = -3,//创建CHANNEL错误
    CHANNEL_DESTROY_ERROR       = -4,//销毁CHANNEL错误
    CHANNEL_CREATE_SELF_REFUSE  = -5,//其他模块要求跟“我”建立channel，“我”拒绝
    CHANNEL_CREATE_FULL         = -6,//channel满了
    CHANNEL_CREATE_ALREADYCLOSE = -7,//本地已经关闭了
    CHANNEL_CREATE_REFUSE       = -8,//对方拒绝建立CHANNEL
    CHANNEL_CREATE_ALREADYBEUSED= -9,//channel ID已经被占用
    CHANNEL_SENDDATA_ERROR      = -10,//数据传输错误，对面模块已经不存在
};

enum CHANNELMODE
{
    CHANNELMODE_DEFAULT         = 0,//默认模式，在一段时间内没有数据传输，直接关闭
    CHANNELMODE_LONG            = 1,//长连接模式，一段时间没有数据传输，也不关闭
    CHANNELMODE_MAX
};

enum CHANNEL_STATUS
{
    CHANNEL_UNUSE,		//未使用
    CHANNEL_USING,		//被占用
    CHANNEL_WAIT_RET,	//等待验证状态
    CHANNEL_USED,		//验证成功并被使用状态
    CHANNEL_CLOSING,	//关闭
};


class IPostHandler;
class IPostChannelHandler;

class IPostAgent
{
public:
    //登录
    virtual bool Login(const char* pszPostIP, unsigned short wPort, const char* szModName = 0, const char* szModKey = 0) = 0;
    //登出
    virtual bool Logout() = 0;
    //周期调用
    virtual void Process() = 0;
    //释放资源
    virtual void Release() = 0;
    //创建channel
    virtual ChannelID_t CreateChannel(const char* pszDstModName, const char* pszDstModKey) = 0;
    //销毁channel
    virtual void DestroyChannel(ChannelID_t nChannelID) = 0;
    //销毁全部channel，除了nChannelID
    virtual void DestroyAllChannels(ChannelID_t nExcepChannelID = INVALID_CHANNELID) = 0;
    //发送消息
    virtual bool SendChannelPacket(ChannelID_t nChannelID, Packet* pPacket) = 0;
    virtual bool SendChannelPacket(ChannelID_t nChannelID, const void* pBuffer, unsigned int dwLength) = 0;
    virtual void SetChannelMode(ChannelID_t nChannelID, CHANNELMODE mode) = 0;

	virtual bool SendUDPPacket(const char *pszdstservername, const void* pdata, unsigned int ui32length) = 0;
    //注册处理器
    virtual void RegisterPostHandler(IPostHandler* pHandler) = 0;
    virtual void RegisterChannelHandler(ChannelID_t dwChannelID, IPostChannelHandler* pHandler) = 0;
    virtual CHANNEL_STATUS GetChannelStatus(ChannelID_t nChannelID) = 0;    
    virtual const char* GetChannelDestModName(ChannelID_t nChannelID) = 0;
};


/**
 * @brief POST回调处理类
 */
class IPostHandler
{
public:
    
	/**
	 * @brief 跟POST连接建立成功，并且验证通过时候的回调
	 *
	 * @param errorCode 返回错误码
	 */
    virtual void OnCreate(short errorCode) = 0;
    //POST断开连接时候的回调函数
    virtual void OnDestroy() = 0;

    virtual void OnChannelCreate(ChannelID_t dwChannelID, const char* modName) =0;
    virtual void OnChannelDestroy(ChannelID_t dwChannelID) =0;
    virtual void OnChannelError(ChannelID_t dwChannelID, unsigned short errorCode) =0;
    virtual void OnUDPReceive(const char *SourceServer, const void *pData, unsigned int dwLength) = 0;
};


/**
 * @brief channel响应回调类
 */
class IPostChannelHandler
{
public:
    virtual void OnChannelRecv(ChannelID_t dwChannelID, const void *pBuffer, unsigned int dwLength) =0;
};

/**
 * @brief 创建POSTAGENT唯一接口
 *
 * @param dwVersion
 * @param dwMaxChannel
 *
 * @return 
 */
#ifdef __APP_BUILD_COMMIT__
/*extern "C" POSTAGENT_API */IPostAgent* CreatePostAgent(unsigned int dwVersion, unsigned int dwMaxChannel);
#else
extern "C" POSTAGENT_API IPostAgent* CreatePostAgent(unsigned int dwVersion, unsigned int dwMaxChannel);
#endif

//#if defined(__POST_AGENT_DLLEXPORT__)
//inline IPostAgent* MyPostAgentCreate(unsigned int dwVersion, unsigned int dwMaxChannel)
//{
//    typedef IPostAgent* (*POSTAGENT_CREATE_FUNC)(unsigned int dwVersion, unsigned int dwMaxChannel);
//    static const HMODULE hPostAgentDll = LoadLibrary("PostAgent.dll");
//    static const POSTAGENT_CREATE_FUNC funcPostAgentCreate = (POSTAGENT_CREATE_FUNC)GetProcAddress(hPostAgentDll, "CreatePostAgent");
//
//    return funcPostAgentCreate(dwVersion, dwMaxChannel);
//}
//#endif 

} // namespace postagent

} // namespace platform 

#endif
