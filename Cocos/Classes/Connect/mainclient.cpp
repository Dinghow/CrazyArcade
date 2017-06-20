#include<iostream>  
#include<string>  
#include<stdio.h>  
#include"ClientNet.h"
#include"client.h"
#include "../GamePlay/Data.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

 //È«¾Ö

void Client()
{
	int rlt = 0;
	string msg;

	if (rlt == 0)
	{
		rlt = client.ClientConnect(8888, ip.c_str());

		msg = "H";
		client.ClientSend(msg.c_str(), msg.length());
		client.ClientClose();
	}
}

void choose()
{
	int rlt = 0;
	rlt = client.ClientConnect(8888, ip.c_str());
	char choose[2] = { 0 };
	choose[0] = myRoleSelect + 48;
	choose[1] = myMapSelect + 48;
	rlt = client.ClientSend(choose, 2);
	client.ClientClose();
}

void message()
{
	memset(mymessage, 0, sizeof(mymessage));
	memset(othermessage, 0, sizeof(othermessage));
	int rlt = 0;
	rlt = client.ClientConnect(8888, ip.c_str());
	
	mymessage[0] = myRoleSelect + 48;
	mymessage[1] = 'M';
	mymessage[2] = myPlayerInformation.isUpPressed + 48;
	mymessage[3] = myPlayerInformation.isDownPressed + 48;
	mymessage[4] = myPlayerInformation.isLeftPressed + 48;
	mymessage[5] = myPlayerInformation.isRightPressed + 48;
	mymessage[6] = myPlayerInformation.isSpacePressed + 48;
	//add
	int x_hun = myPlayerInformation.role_x / 100;
	int x_ten = (myPlayerInformation.role_x - x_hun * 100) / 10;
	int x_ge = myPlayerInformation.role_x - x_ten * 10 - x_hun * 100;
	mymessage[7] = x_hun + 48;
	mymessage[8] =x_ten + 48;
	mymessage[9] = x_ge + 48;
	int y_hun = myPlayerInformation.role_y / 100;
	int y_ten = (myPlayerInformation.role_y - y_hun * 100) / 10;
	int y_ge = myPlayerInformation.role_y - y_ten * 10 - y_hun * 100;
	mymessage[10] = y_hun + 48;
	mymessage[11] = y_ten + 48;
	mymessage[12] = y_ge + 48;
	mymessage[13] = myPlayerInformation.bomb_x + 48;
	mymessage[14] = myPlayerInformation.bomb_y + 48;
	int t_hun = gameTime / 100;
	int t_ten = (gameTime - t_hun * 100) / 10;
	int t_ge = gameTime - t_hun * 100 - t_ten * 10;
	mymessage[15] = t_hun + 48;
	mymessage[16] = t_ten + 48;
	mymessage[17] = t_ge + 48;
	mymessage[18] = closeServer + 48;
	

	rlt = client.ClientSend(mymessage,sizeof(mymessage));

	client.ClientClose();
}
