#ifndef _ROLE_H_
#define _ROLE_H_

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
class Role {
private:
	CCPoint position;
	int bombQuantity;
	float bombRange;
	int speed;
public:
	CCSprite* role;
	Role();
	int getSpeed() { return speed; }
	void addspeed() { speed++; }
	void loadPositon();
	CCPoint getPosition() { return position; }
	void setPosition(CCPoint& r) { position = r;}
	void addBombRange() { bombRange++; }
};


#endif
