#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Bomb.h"
#include <strstream>
#include "GameOver.h"
USING_NS_CC;
class cBomb;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace std;

extern Player* m_Roles[2];

class MapOfGame : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	RoleDirection direction;
	RoleDirection direction2;
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	//void menuCloseCallback(CCObject* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(MapOfGame);
	Node* _cursor;
	virtual ~MapOfGame();
	cocos2d::SpriteFrameCache* cache;
	cocos2d::CCTMXTiledMap* gameMap;
	CCLabelAtlas* numberAtlas;
	Player role1;
	Player role2;
	int seconds;
	friend CollisionType checkCollision(cocos2d::CCPoint rolePosition, cocos2d::CCPoint targetPosition, RoleDirection direction);

	void menuCallbackMove(CCObject *pSender);
	void opponentBehavior(float dt);
	void moveUpdate(float delta);
	void update(float dt);
	void timer(float delta);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	
	void bombKillCheck(Player* role,vector<cBomb*>& vcBombs);
	void killRole(Player* role);
	void detonateKill(Player* role1, Player* role2);
	void BackTouch(cocos2d::Ref* pSender, Widget::TouchEventType type);
	void judgeResult(bool isWin);
	void backToRoom();
	void playResultMusic();
	void playMusic(float dt);
	void bombForcedDetonate();
	void onEnter();
	void onExit();
	void cleanup();
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};


#endif // __PLAY_SCENE_H__

