#include "Data.h"

int map_tag = 0;
int role_tag = 0;
bool test_model = false;
int opponent = 0;
bool isMeAlive = false;
bool shouldBack = false;
bool hasJudgeRun = false;
bool hasBackRun = false;
bool hasBeginRun = false;
int myMapSelect = 0;
int otherMapSelect1 = 0;
int myRoleSelect = 0;
int otherRoleSelect1 = 0;
int gamecanbegin = 0;
char gamecanstart[1] = { 0 };
char recv_[18] = { 0 };
char mymessage[18] = { 0 };
char othermessage[18] = { 0 };
char itemInfo[195] = { 0 };
bool isHost = false;
int itemNo = 0;
int gameTime = 0;
int bombNumber = 0;
ClientNet client;
std::string ip = "0";
playerInformation myPlayerInformation = { false,false,false,false,false,0,0,0,0 };
playerInformation otherPlayerInformation = { false,false,false,false,false,0,0,0,0 };