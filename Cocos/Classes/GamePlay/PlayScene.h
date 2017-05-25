#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

class MapOfGame : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MapOfGame);
	virtual ~MapOfGame();
	cocos2d::CCTMXTiledMap *map;
	cocos2d::CCAnimation* walkAnimations[4];
	cocos2d::CCSprite* role1;
	typedef enum {
		kUp,
		kDown,
		kLeft,
		kRight,
		kTotal,
	}RoleDirection;
	cocos2d::CCAnimation* creatAnimationByDirecton(RoleDirection direciton);

	void menuCallbackMove(CCObject *pSender);
	void setFaceDirection(RoleDirection direction);
	void onWalkDone(CCNode *pTarget, void *data);
	bool isRoleWalking;
	cocos2d::CCPoint positionForTileCoord(cocos2d::CCPoint tileCoord);
	cocos2d::CCPoint tilecoordForPosition(cocos2d::CCPoint position);
	void update(float dt);
	typedef enum {
		kNone,
		kWall,
	}CollisionType;

	CollisionType checkCollision(cocos2d::CCPoint rolePosition);
private:
};

#endif // __PLAY_SCENE_H__

