#ifndef _CLIENTNET_H_
#define _CLIENTNET_H_

#include<windows.h> 

class ClientNet
{
private:
	SOCKET m_sock;

public:
	// 连接指定的服务器  
	int ClientConnect(int port, const char* address);
	// 发送信息  
	int ClientSend(const char* msg, int len);
	// 关闭连接  
	void ClientClose();
};

#endif // _CLIENTNET_H_