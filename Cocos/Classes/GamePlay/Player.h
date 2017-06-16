#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Bomb.h"
#include "Item.h"
#include "Data.h"
#include <vector>
USING_NS_CC;
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

class cBomb;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace std;

typedef enum {
	kNone,
	kWall,
}CollisionType;

typedef struct {
	bool isUpPressed;
	bool isDownPressed;
	bool isLeftPressed;
	bool isRightPressed;
	bool isSpacePressed;
}playerInfomation;

typedef enum {
	kUp,
	kDown,
	kLeft,
	kRight,
	kTotal,
}RoleDirection;

//the role class include basic role properties
class Player : public cocos2d::Layer
{
private:
	CCPoint position;
	int bombQuantity;
	int bombRange;
	float speed;
	float preSpeed;
	int money;

	int speedLimit;
	int bombQuantityLimit;
	float m_CanNotBeKilledTime;
	float m_DeadTime;
	bool m_Killed;
	bool m_Deleted;
	bool m_Dying;
	bool m_CanNotBeKilled;
public:
	int onRide;
	int roleSelection;
	vector<cBomb*> m_Bombs;
	CCSprite* role;
	CCSprite* shadow;
	CCPoint startPosition;
	Player();
	/********************* Set this player's information ****************************************/
	playerInfomation playerInfo;
	bool isOpponent;
	/********************* Set this player's role *********************************/
	void roleInit(CCTMXObjectGroup *objects,cocos2d::SpriteFrameCache* cache,int spawnpoint,int roleSelect,int isOpp);
	//role animation
	Vector<SpriteFrame*> frameArray1;
	Vector<SpriteFrame*> frameArray2;
	cocos2d::Animation* deadAnimations[2];
	cocos2d::CCAnimation* walkAnimations[3][4];
	cocos2d::RepeatForever* animations[4];
	cocos2d::SpriteFrame* faceFrames[3][4];
	cocos2d::CCAnimation* creatAnimationByDirecton(int ride, RoleDirection direciton, cocos2d::SpriteFrameCache* cache);
	void setFaceDirection(RoleDirection direction);
	void onWalkDone(RoleDirection direction);
	//role move
	void keyPressedAnimation(EventKeyboard::KeyCode keyCode);
	void keyPressedMovement(EventKeyboard::KeyCode keyCode);
	friend CollisionType checkCollision(cocos2d::CCPoint rolePosition, cocos2d::CCPoint targetPosition, RoleDirection direction);
	//speed property
	void setProperties(float speed = 6.5, int bombRange = 2, int bombQuantity = 1, int speedLimit = 15, int bombQuantityLimit = 4);
	int getSpeed() { return speed; }
	void addSpeed() { 
		if (++speed > speedLimit)
			speed = speedLimit;
		if (++preSpeed > speedLimit)
			preSpeed = speedLimit;
	}
	//position property
	void loadPositon();
	CCPoint getPosition() { return position; }
	void setPosition(CCPoint& r) { position = r;}
	//bomb property
	void addBombRange();
	//Pick up items
	void pickUpItem(const cocos2d::CCPoint &tilePos);
	//Role on ride
	void roleOnRide(const int &No);
	
	/********************* Function about bomb ********************************/
	//drop bomb
	void dropBomb();
	void addBomb();
	void getKilled();
	void canNotBeKilledUpdate(float dt);
	bool killedOrNot() {
		return m_Killed;
	}
	void getSaved()
	{
		m_Killed = false;
	}
	int showBombRange()
	{
		return bombRange;
	}
	bool deletedOrNot()
	{
		return m_Deleted;
	}
	void setDeleted()
	{
		m_Deleted = true;
	}
	bool dyingOrNot()
	{
		return m_Dying;
	}
	void setDying()
	{
		m_Dying = true;
	}
	Animation* createDyingAnimation();
	Animation* createDeleteAnimation();
	void roleDying();
	void roleDelete();
	void setRoleDead();
	void deadUpdate(float dt);
	void detonateKill()
	{
		if(m_DeadTime<=5.7)
			m_DeadTime = 5.6;
	}
};

void initFaceDirection(Player* Roles[2], cocos2d::SpriteFrameCache* cache);
#endif