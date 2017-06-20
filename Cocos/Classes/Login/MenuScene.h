#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;

class MenuTable : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MenuTable);
	void onEnter();
	void onExit();
	void cleanup();
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();

private:
	void ReturnMainTouch(cocos2d::Ref* pSender, Widget::TouchEventType type);
	void AboutTouch(cocos2d::Ref* pSender, Widget::TouchEventType type);
	void PlusTouch(cocos2d::Ref* pSender, Widget::TouchEventType type);
	void MinusTouch(cocos2d::Ref* pSender, Widget::TouchEventType type);
};

#endif // __MENU_SCENE_H__
