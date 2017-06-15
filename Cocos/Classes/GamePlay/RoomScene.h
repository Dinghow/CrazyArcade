#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

class Room : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "statiac create()" method manually
	CREATE_FUNC(Room);
	CheckBox* m_checkbox1;
	CheckBox* m_checkbox2;
	CheckBox* m_checkbox3;
	CheckBox* r_checkbox1;
	CheckBox* r_checkbox2;
	ImageView* m_thumbnail;
	ImageView* r_thumbnail;
	ImageView* m_blank;
	ImageView* r_blank;
	void onEnter();
	void onExit();
	void cleanup();
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();
private:
	void PlayTouch(cocos2d::Ref* pSender, Widget::TouchEventType type);
	void BackTouch(Ref* pSender, Widget::TouchEventType type);
	void m_checkBoxCallback1(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
	void m_checkBoxCallback2(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
	void m_checkBoxCallback3(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
	void r_checkBoxCallback1(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
	void r_checkBoxCallback2(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
};

#endif // __ROOM_SCENE_H__

