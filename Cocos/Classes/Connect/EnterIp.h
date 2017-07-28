#ifndef __ENTER_LAYER_H__
#define __ENTER_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
class ENTER : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	Layout*root;
	Button* btnConfirm;
	TextField* textField;
	
	void ConfirmTouch(cocos2d::Ref* pSender, Widget::TouchEventType type);
	void textFieldEvent(Ref* pSender, TextField::EventType type);
	// implement the "static create()" method manually
	CREATE_FUNC(ENTER);
	Node* _cursor;
	void onEnter();
	void onExit();
	void cleanup();
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();
};

#endif // __ENTER_SCENE_H__
