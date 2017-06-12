#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Item.h"
#include "Bomb.h"
#include "Item.h"
#include <vector>
USING_NS_CC;
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

class cBomb;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace std;
//the role class include basic role properties
class Role : public cocos2d::Layer
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
	Role();
	void setProperties(int speed = 6.5, int bombRange = 1, int bombQuantity = 1);
	//speed property
	int getSpeed() { return speed; }
<<<<<<< HEAD
<<<<<<< HEAD
	void addSpeed() { speed += 0.7; }
=======
	void addSpeed() { speed++; }
>>>>>>> origin/zhc
=======
	void addSpeed() { speed += 0.7; }
>>>>>>> origin/hpc
	//position property
	void loadPositon();
	CCPoint getPosition() { return position; }
	void setPosition(CCPoint& r) { position = r;}
	//bomb property
	void addBombRange();
	//Pick up items
	void pickUpItem(const cocos2d::CCPoint &tilePos);
	
	/*****************************************************/
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
	Animation* createDeadAnimation();
	void setRoleDead();
	void deadUpdate(float dt);
};


#endif
