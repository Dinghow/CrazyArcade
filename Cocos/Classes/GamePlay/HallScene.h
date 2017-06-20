#pragma once
#ifndef __HALL_SCENE_H__
#define __HALL_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

class Hall : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "statiac create()" method manually
	CREATE_FUNC(Hall);
	void transferInspect(float dt);
private:
	void StartTouch(cocos2d::Ref* pSender, Widget::TouchEventType type);
	void ConnectTouch(Ref* pSender, Widget::TouchEventType type);
	void MenuTouch(Ref* pSender, Widget::TouchEventType type);
	void ExitTouch(Ref* pSender, Widget::TouchEventType type);
	void BackTouch(Ref* pSender, Widget::TouchEventType type);
	void TestTouch(Ref* pSender, Widget::TouchEventType type);
};

#endif // __HALL_SCENE_H__

