#ifndef __ITEM_H__
#define __ITEM_H__
#include "cocos2d.h"
#define PROBABILITY 0.8

class Item : public cocos2d::Node
{
public:
	Item(int &itemNo, const cocos2d::CCPoint &TPos, cocos2d::CCTMXTiledMap* Map);
	~Item() { remove(); }
	void remove();
	cocos2d::CCPoint getItemPosition();
private:
	cocos2d::Sprite* item;
	cocos2d::Sprite* shadow;
	cocos2d::CCTMXTiledMap* Map;
	cocos2d::CCPoint tilePos;
};
//random number generator
int randNum();

//random item at a random place
int randomItem(const cocos2d::CCPoint &itemPos, cocos2d::CCTMXTiledMap* Map);

#endif; //__ITEM_H__
