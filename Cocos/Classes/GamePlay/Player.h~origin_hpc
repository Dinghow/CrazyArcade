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
typedef struct {
	bool isUpPressed;
	bool isDownPressed;
	bool isLeftPressed;
	bool isRightPressed;
	bool isSpacePressed;
}playerInfomation;

//the role class include basic role properties
class Player : public cocos2d::Layer
{
private:
	CCPoint position;
	int bombQuantity;
	int bombRange;
	float speed;
	int money;
	float m_DeadTime;
	bool m_Killed;
	bool m_Deleted;
	bool m_Dying;
public:
	vector<cBomb*> m_Bombs;
	CCSprite* role;
	CCSprite* shadow;
	CCPoint startPosition;
	Player();
	/********************* Set this player's information ****************************************/
	playerInfomation playerInfo;
	/********************* Set this player's role *********************************/
	void roleInit(CCTMXObjectGroup *objects,cocos2d::SpriteFrameCache* cache,int spawnpoint);
	void setProperties(int speed = 6.5, int bombRange = 1, int bombQuantity = 1);
	//speed property
	int getSpeed() { return speed; }
	void addSpeed() { speed += 0.7; }
	//position property
	void loadPositon();
	CCPoint getPosition() { return position; }
	void setPosition(CCPoint& r) { position = r;}
	//bomb property
	void addBombRange();
	//Pick up items
	void pickUpItem(const cocos2d::CCPoint &tilePos);
	
	/********************* Function about bomb ********************************/
	//drop bomb
	void dropBomb();
	void addBomb();
	bool killedOrNot() {
		return m_Killed;
	}
	void getKilled()
	{
		m_Killed = true;
		speed = 1.5;
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
		m_DeadTime = 5.6;
	}
};


#endif
