#ifndef _IDEFINE_H
#define _IDEFINE_H
#include <vector>
#include <string>
#ifdef ____WIN32_
#include <WinSock2.h>
#pragma comment<lib,"ws2_32">
#endif

#define MAX_USER_SOCKETFD 1000000
#define MAX_EXE_LEN 200
#define MAX_FILENAME_LEN 250
#define MAX_KEEPALIVE_VALS IOC_IN |IOC_VENDOR |4
#define MAX_MD5_LEN 35
#define MAX_IP_LEN 20

#define LOG_MSG printf 

#ifdef ____WIN32_

#define RELEASE_POINTER(p) {if(p !=NULL)(delete p;p=NULL;)}
#define RELEASE_HANDLE(h) {if(h!=NULL && h!=INVALID_HANDLE_VALUE){CloseHandle(h);h=INVALID_HANDLE_VALUE;}}
#define RELEASE_SOCKET(s) {if(s!INVALID_SOCKET){closesocket(s);s=INVALID_SOCKET;}}
#endif // ____WIN32_
  
typedef signed char           s8;
typedef signed short          s16;
typedef signed int            s32;
typedef signed long long      s64;
typedef unsigned char         u8;
typedef unsigned short        u16;
typedef unsigned int          u32;
typedef unsigned long long    u64;

namespace func
{
	enum SOCKET_CLOSE
	{
		S_CLOSE_FREE = 0,
		S_CLOSE_ACCEPT = 1,  //连接出错关闭
		S_CLOSE_SHUTDOWN=2,  //关闭连接
		S_CLOSE_CLOSE=3      //正式关闭
	};

	enum SOCKET_CONTEXT_STATE
	{
		SC_WAIT_ACCEPT=0,
		SC_WAIT_RECV = 1,
		SC_WAIT_SEND = 2,
		SC_WAIT_RESET = 3
	};

	enum S_SOCKET_STATE
	{
		S_FREE=0,
		S_Connect=1,
		S_ConnectSecure=2,
		S_Login=3,
		S_NeedSave=4,
		S_Saving=5
	};

	struct ConfigXML
	{
		s32 ID;
		u8  Type;
		u16 Port;
		s32 MaxPlayer;//最大玩家数
		s32 MaxConnect;//最大连接量
		u8  RCode;
		s32 Version; //版本号
		s32 ReceOne;//服务器端一次最多接受多少字节数据
		s32 ReceMax;//服务器接受缓冲区
		s32 SendOne;//服务器端一次最多发送多少字节数据
		s32 SendMax;//服务器发送缓冲区
		s32 HeartTime; 
		s32 AutoTime;
		s32 MaxAccpet;
		s32 MaxRece;
		s32 MaxSend;
		char SafeCode[20];
		char Head[3];
		char IP[MAX_IP_LEN];
	};

	struct ServerListXML
	{
		s32 ID;
		u16 Port;
		char IP[MAX_IP_LEN];
	};

	extern char FileExePath[MAX_EXE_LEN];
	extern ConfigXML* __ServerInfo;
	extern ConfigXML* __ClientInfo;
	extern std::vector<ServerListXML*>__ServerListInfo;
	extern void(*MD5str)(char* output, unsigned char* input, int len);
	extern bool InitData();
}

#endif // !_IDEFINE_H

