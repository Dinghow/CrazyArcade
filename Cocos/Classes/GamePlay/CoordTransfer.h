#ifndef __COORD_TRANSFER__
#define __COORD_TRANSFER__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace std;

extern cocos2d::CCTMXTiledMap* theMap;
cocos2d::CCPoint positionForTileCoord(cocos2d::CCPoint tileCoord);
cocos2d::CCPoint tilecoordForPosition(cocos2d::CCPoint position);
#endif