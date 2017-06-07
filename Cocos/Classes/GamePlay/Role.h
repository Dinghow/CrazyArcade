#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Bomb.h"
#include <vector>
USING_NS_CC;

class cBomb;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace std;
//the role class include basic role properties
class Role {
private:
	CCPoint position;
	int bombQuantity;
	int bombRange;
	float speed;
public:
	vector<cBomb*> m_Bombs;
	CCSprite* role;
	CCSprite* shadow;
	CCPoint startPosition;
	Role();
	//speed property
	int getSpeed() { return speed; }
	void addspeed() { speed++; }
	//position property
	void loadPositon();
	CCPoint getPosition() { return position; }
	void setPosition(CCPoint& r) { position = r;}
	//bomb property
	void addBombRange();
	//drop bomb
	void dropBomb();
	void addBomb();
};


#endif
