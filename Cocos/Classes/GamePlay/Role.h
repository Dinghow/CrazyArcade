#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
//the role class include basic role properties
class Role {
private:
	CCPoint position;
	int bombQuantity;
	float bombRange;
	float speed;
public:
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
	void addBombRange() { bombRange++; }
};


#endif
