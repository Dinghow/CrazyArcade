#ifndef __PROP_
#define __PROP_
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Role.h"
USING_NS_CC;


class cProp
{
public:
	enum buff
	{
		QUANTITY = 1,
		RANGE,
		SPEED_ADD,
	};
private:
	buff m_Kind;
	CCPoint m_tPosition;
	CCSprite* m_Role;
	cocos2d::CCTMXTiledMap* m_Map;
	CCSprite* m_Sprite;
public:
	cProp(buff kind, CCPoint tposition) :m_Kind(kind), m_tPosition(tposition) { }
	CCSprite* createPropSprite(buff kind);
	void createProp();
	void removeProp();
};

#endif // !__PROP_


