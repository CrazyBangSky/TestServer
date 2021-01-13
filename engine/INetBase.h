#ifndef _INETBASE_H
#define _INETBASE_H

#include "IDefine.h"

namespace net
{

#pragma pack(push,packing)
#pragma (1)
	//客户端连接数据索引
	struct S_CLIENT_BASE_INDEX
	{
		s32 index;
		inline void Reset() { index = -1; }
	};
	//客户端连接数据
	struct S_CLIENT_BASE
	{
#ifdef ____WIN32_
		SOCKET socketfd;
#else
		int socketfd;
#endif 
		s8 state;//记录当前socket连接状态
		s8 closeState;//记录当前socket关闭状态
		char ip[MAX_IP_LEN];
		u16 port;
		s32 ID;//当前玩家连接数据ID，就是索引下标
		u8 rCode;
		s32 ClientID;
		u8 ClientType;

		//接收数据
		bool is_RecvCompleted;
		char* recvBuf;//存放接收数据
		char* recvBuf_Tmep;//临时存放
		s32 recv_Head;
		s32 recv_Tail;
		s32 recv_TempHead;
		s32 recv_TempTail;
		
		//发送数据
		bool is_Sending;
		bool is_SendCompleted;
		char* sendBuf;//存放发送数据
		s32 send_Head;
		s32 send_Tail;
		s32 send_TempTail;

		//时间类
		s32 time_Connent;
		s32 time_Heart;
		s32 time_Close;
		u8 threadID;
		s32 shutdown_kind;
		char md5[MAX_MD5_LEN];

		void init();
		void Reset();
#ifdef ____WIN32_
		inline bool isT(SOCKET fd)
		{
			if (socketfd == fd)return true;
			return false;
		}
#else
		inline bool isT(int fd)
		{
			if (socketfd == fd)return true;
			return false;
		}
#endif
	};
#pragma pack(pop,packing)

	class ITcpServer;
	typedef bool(*TCPSERVERNOTIFY_EVENT)(ITcpServer* tcp, S_CLIENT_BASE* c, const s32 code);


	class ITcpServer
	{
	public:
	virtual	~ITcpServer();
	virtual void runServer(int num) = 0;
#ifdef ____WIN32_
	virtual S_CLIENT_BASE* client(SOCKET fd,bool issecurity) = 0;
#else
	virtual S_CLIENT_BASE* client(int fd, bool issecurity) = 0;
#endif
	virtual S_CLIENT_BASE* client(int index) = 0;
	};

	extern ITcpServer* NewTcpServer();

}





#endif // _INETBASE_H
