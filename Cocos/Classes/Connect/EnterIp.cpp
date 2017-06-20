#include "EnterIp.h"
#include <string>
#include "../GamePlay/HallScene.h"
#include "../GamePlay/Data.h"
#include "client.h"

USING_NS_CC;

using namespace cocostudio::timeline;
// on "init" you need to initialize your instance
bool ENTER::init()
{
	ip = "0";
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("HallScene/IpLayer.csb");
	Layout* background = (Layout*)rootNode->getChildByName("panel");
	btnConfirm = (Button*)Helper::seekWidgetByName( background,"confirm_button");
	textField = (TextField*)Helper::seekWidgetByName(background, "text_field");
	textField->attachWithIME();
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ENTER:
			log("Enter");
			ip = textField->getString();
			Client();
			this->removeFromParentAndCleanup(true);
			break;
		}
	};
	
	textField->addEventListener(CC_CALLBACK_2(ENTER::textFieldEvent, this));
	btnConfirm->addTouchEventListener(CC_CALLBACK_2(ENTER::ConfirmTouch, this));

	addChild(rootNode);
	return true;
}

void ENTER::ConfirmTouch(cocos2d::Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		ip = textField->getString();
		Client();
		this->removeFromParentAndCleanup(true);
		break;
	}
}

void ENTER::textFieldEvent(Ref* pSender, TextField::EventType type) {
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
		break;
	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
		break;
	case cocos2d::ui::TextField::EventType::INSERT_TEXT:
		break;
	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
		break;
	default:
		break;
	}
}

void ENTER::onEnter() {
	Layer::onEnter();
}

void ENTER::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	//play music
}

void ENTER::onExit() {
	Layer::onExit();
}

void ENTER::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
}

void ENTER::cleanup() {
	Layer::cleanup();
}

