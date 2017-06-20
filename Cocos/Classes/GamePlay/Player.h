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

typedef enum {
	kUp,
	kDown,
	kLeft,
	kRight,
	kTotal,
	kStop,
	kStart,
}RoleDirection;

//the role class include basic role properties
class Player : public cocos2d::Layer
{
private:
	CCPoint position;
	int bombQuantity;
	int bombRange;
	int money;
	int speedLimit;
	int bombQuantityLimit;
	float speed;
	float preSpeed;
	float m_CanNotBeKilledTime;
	float m_DeadTime;
	bool m_Killed;
	bool m_Deleted;
	bool m_Dying;
	bool m_CanNotBeKilled;
public:
	int onRide;
	int roleSelection;
	bool hasUpReleased;
	bool hasDownReleased;
	bool hasLeftReleased;
	bool hasRightReleased;
	RoleDirection nowDirection;
	vector<cBomb*> m_Bombs;
	CCSprite* role;
	CCSprite* shadow;
	CCPoint startPosition;
	Player();
	/********************* Set this player's information ****************************************/
	bool isOpponent;
	/********************* Set this player's role *********************************/
	void roleInit(CCTMXObjectGroup *objects,cocos2d::SpriteFrameCache* cache,int roleSelect,int isOpp);
	//role animation
	Vector<SpriteFrame*> frameArray1;
	Vector<SpriteFrame*> frameArray2;
	cocos2d::Animation* deadAnimations[2];
	cocos2d::CCAnimation* walkAnimations[3][4];
	cocos2d::RepeatForever* animations[4];
	cocos2d::SpriteFrame* faceFrames[3][4];
	cocos2d::CCAnimation* creatAnimationByDirecton(int ride, RoleDirection direction, cocos2d::SpriteFrameCache* cache);
	void setFaceDirection(RoleDirection direction);
	void onWalkDone(RoleDirection direction);
	//role move
	void keyPressedAnimation(RoleDirection direction);
	void keyPressedMovement(EventKeyboard::KeyCode keyCode);
	friend CollisionType checkCollision(cocos2d::CCPoint rolePosition, cocos2d::CCPoint targetPosition, RoleDirection direction);
	//speed property
	void setProperties(float speed, int bombRange, int bombQuantity, int speedLimit, int bombQuantityLimit);
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
	void dropBomb(int x, int y);
	void addBomb();
	void canNotBeKilledUpdate(float dt);
	void getKilled();
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
