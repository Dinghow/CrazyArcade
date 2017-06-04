#include "RoomScene.h"
#include "../Login/LoginScene.h"
#include "PlayScene.h"
#include "Data.h"

Scene* Room::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Room::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Room::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("RoomScene/RoomScene.csb");
	Layout* background = (Layout*)rootNode->getChildByName("background");
	Button* btnConfirm = (Button*)Helper::seekWidgetByName(background, "confirm_button");
	Button* btnExit = (Button*)Helper::seekWidgetByName(background, "exit_button");
	checkbox1 = (CheckBox*)Helper::seekWidgetByName(background, "check_box1");
	checkbox2 = (CheckBox*)Helper::seekWidgetByName(background, "check_box2");
	blank = (ImageView*)Helper::seekWidgetByName(background, "thumbnail");
	
	btnConfirm->addTouchEventListener(CC_CALLBACK_2(Room::PlayTouch, this));
	btnExit->addTouchEventListener(CC_CALLBACK_2(Room::BackTouch, this));
	checkbox1->addEventListener(CC_CALLBACK_2(Room::checkBoxCallback1, this));
	checkbox2->addEventListener(CC_CALLBACK_2(Room::checkBoxCallback2, this));

	addChild(rootNode);

	return true;
}

void Room::PlayTouch(cocos2d::Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		//transfer to MapScene
		auto scene = MapOfGame::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		director->pushScene(transition);

		break;
	}
}

void Room::BackTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		//transfer to MapScene
		auto scene = Login::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->pushScene(transition);

		break;
	}
}

void Room::checkBoxCallback1(cocos2d::Ref * ref, CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		checkbox2->setSelectedState(false);
		thumbnail = ImageView::create("RoomScene/map1.png");
		thumbnail->setAnchorPoint(Vec2(0,0));
		thumbnail->setPosition(ccp(0,0));
		blank->addChild(thumbnail);
		map_tag = 1;
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		break;
	default:
		break;
	}
}

void Room::checkBoxCallback2(cocos2d::Ref * ref, CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		checkbox1->setSelectedState(false);
		thumbnail = ImageView::create("RoomScene/map2.png");
		thumbnail->setAnchorPoint(Vec2(0, 0));
		thumbnail->setPosition(ccp(0, 0));
		blank->addChild(thumbnail);
		map_tag = 2;
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		break;
	default:
		break;
	}
}