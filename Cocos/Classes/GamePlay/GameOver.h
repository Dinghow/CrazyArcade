#ifndef __OVER_LAYER_H__
#define __OVER_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Data.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
class GameOver : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void update(float dt);
	void backToMap();
	float time;

	Layout*root;
	ImageView* imag;
	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);
	void onEnter();
	void onExit();
	void cleanup();
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();
};

#endif // __HELLOWORLD_SCENE_H__

