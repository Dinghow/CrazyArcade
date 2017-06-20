#include<iostream>  
#include<string>  
#include<stdio.h>  
#include"ClientNet.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main()
{
	ClientNet client;
	int rlt = 0;
	string msg;
	//memset(msg, 0, sizeof(msg));  
	printf("connecting.....\n");

	//连接成功
	if (rlt == 0)
	{
		rlt = client.ClientConnect(8888, "127.0.0.1");
		printf("    connect successfully. input  q to quit\n");
		printf("-------------------------\n");
		msg = "H";
		client.ClientSend(msg.c_str(), msg.length());
		printf("closing socket.....\n");
		client.ClientClose();
	}

	while (rlt == 0)
		// socket连接成功  
	{
		rlt = client.ClientConnect(8888, "127.0.0.1");
		//发送消息  
		printf("    connect successfully. input  q to quit\n");
		printf("-------------------------\n");
		
		char choose[2] = { 0 };
		choose[0] = 1;
		choose[1] = 1;
		printf("sending msg.....\n");
		rlt = client.ClientSend(choose, 2);
		

		// 关闭socket  
		printf("closing socket.....\n");
		client.ClientClose();
	}

	system("pause");
	return 0;
}