#ifndef __DATA_H__
#define __DATA_H__
#include <string>
#include"../Connect/ClientNet.h"
//used to bulid connection among different files
typedef struct {
	bool isUpPressed;
	bool isDownPressed;
	bool isLeftPressed;
	bool isRightPressed;
	bool isSpacePressed;
	int role_x;
	int role_y;
	int bomb_x;
	int bomb_y;
}playerInformation;

extern int map_tag;
extern int role_tag;
extern bool test_model;
extern int opponent;
extern bool isMeAlive;
extern bool shouldBack;
extern bool hasBackRun;
extern bool hasJudgeRun;
extern bool hasBeginRun;
extern int myMapSelect;
extern int otherMapSelect1;
extern int myRoleSelect;
extern int otherRoleSelect1;
extern int gamecanbegin;
extern std::string ip;
extern char gamecanstart[1];
extern char recv_[213];
extern char mymessage[213];
extern char othermessage[213];
extern char itemInfo[195];
extern ClientNet client;
extern playerInformation myPlayerInformation;
extern playerInformation otherPlayerInformation;
extern bool isHost;
extern int itemNo;
extern int gameTime;
extern int bombNumber;
//used to connect different players

#endif
