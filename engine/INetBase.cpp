#include "INetBase.h"
#include<time.h>
#include<string.h>
#ifdef ____WIN32_
#else
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#endif

namespace func
{
	char FileExePath[MAX_EXE_LEN];
	ConfigXML* __ServerInfo=NULL;
	ConfigXML* __ClientInfo=NULL;
	std::vector<ServerListXML*>__ServerListInfo;
	void(*MD5str)(char* output, unsigned char* input, int len)=NULL;
	bool InitData()
	{
		memset(FileExePath, 0, MAX_EXE_LEN);
#ifdef ____WIN32_
		GetModuleFileNameA(NULL, (LPSTR)FileExePath, MAX_EXE_LEN);
		std::string str(FileExePath);
		size_t pos = str.find_last_of("\\");
		str = str.substr(0, pos + 1);
		memcpy(FileExePath, str.c_str(), MAX_EXE_LEN);
#else
		int ret = readlink("/proc/self/exe", FileExePath, MAX_EXE_LEN);
		std::string str(FileExePath);
		size_t pos = str.find_last_of("/");
		str = str.substr(0, pos + 1);
		memcpy(FileExePath, str.c_str(), MAX_EXE_LEN);
#endif
		LOG_MSG("FileExePath:%s \n", FileExePath);
		return false;
	}
}
namespace net
{
	void net::S_CLIENT_BASE::init()
	{
		recvBuf = new char[func::__ServerInfo->ReceMax];
		sendBuf = new char[func::__ServerInfo->SendMax];
		Reset();
	}

	void net::S_CLIENT_BASE::Reset()
	{
#ifdef ____WIN32_
		socketfd = INVALID_SOCKET;
#else
		socketfd = -1;
#endif 
		//接收数据初始化
		port = 0;
		ID = -1;
		rCode = func::__ServerInfo->RCode;
		recv_Head = 0;
		recv_Tail = 0;
		recv_TempHead = 0;
		recv_TempTail = 0;
		is_RecvCompleted = 0;
		//发送数据初始化
		send_Head = 0;
		send_Tail = 0;
		send_TempTail = 0;
		is_SendCompleted = true;
		is_Sending = false;
		//时间类初始化
		time_Connent=(int)time(NULL);
		time_Heart= (int)time(NULL);
		time_Close= (int)time(NULL);
		threadID=0;
		
		memset(recvBuf, 0, func::__ServerInfo->ReceMax);
		memset(sendBuf, 0, func::__ServerInfo->SendMax);
		memset(ip, 0, MAX_IP_LEN);

		closeState = 0;
		state = func::S_FREE;


	}

}

