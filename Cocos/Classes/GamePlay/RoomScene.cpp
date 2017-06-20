#include "RoomScene.h"
#include "HallScene.h"
#include "PlayScene.h"
#include "Data.h"
#include "../Connect/client.h"

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
	if (test_model == true)
		isHost = true;
	gamecanstart[0] = { 0 };
	shouldBack = false;
	hasBackRun = false;
	hasJudgeRun = false;
	hasBeginRun = false;
	isMeAlive = false;
	gamecanbegin = 0;
	myMapSelect = 0;
	myRoleSelect = 0;
	auto rootNode = CSLoader::createNode("RoomScene/RoomScene.csb");
	Layout* background = (Layout*)rootNode->getChildByName("background");
	//get button and checkbox from the csb file
	Button* btnConfirm = (Button*)Helper::seekWidgetByName(background, "confirm_button");
	Button* btnExit = (Button*)Helper::seekWidgetByName(background, "exit_button");
	//map select button
	m_checkbox1 = (CheckBox*)Helper::seekWidgetByName(background, "m_check_box1");
	m_checkbox2 = (CheckBox*)Helper::seekWidgetByName(background, "m_check_box2");
	m_checkbox3 = (CheckBox*)Helper::seekWidgetByName(background, "m_check_box3");
	m_blank = (ImageView*)Helper::seekWidgetByName(background, "m_thumbnail");
	//role select button
	r_checkbox1 = (CheckBox*)Helper::seekWidgetByName(background, "r_check_box1");
	r_checkbox2 = (CheckBox*)Helper::seekWidgetByName(background, "r_check_box2");
	r_blank = (ImageView*)Helper::seekWidgetByName(background, "r_thumbnail");
	//text
	text = (Text*)Helper::seekWidgetByName(background, "text");

	btnConfirm->addTouchEventListener(CC_CALLBACK_2(Room::PlayTouch, this));
	btnExit->addTouchEventListener(CC_CALLBACK_2(Room::BackTouch, this));
	m_checkbox1->addEventListener(CC_CALLBACK_2(Room::m_checkBoxCallback1, this));
	m_checkbox2->addEventListener(CC_CALLBACK_2(Room::m_checkBoxCallback2, this));
	m_checkbox3->addEventListener(CC_CALLBACK_2(Room::m_checkBoxCallback3, this));
	r_checkbox1->addEventListener(CC_CALLBACK_2(Room::r_checkBoxCallback1, this));
	r_checkbox2->addEventListener(CC_CALLBACK_2(Room::r_checkBoxCallback2, this));

	this->scheduleUpdate();
	addChild(rootNode);

	return true;
}

void Room::update(float dt) {
	if (test_model == false) {
		if (myMapSelect != 0 && myRoleSelect != 0) {
			choose();
		}
		else {
			text->setText("请选择地图和不同角色");
		}
		if (recv_[0] == '1') {
			notification = "The other choose map1";
		}
		else if (recv_[0] == '2') {
			notification = "The other choose map2";
		}
		else if (recv_[0] == '3') {
			notification = "The other choose map3";
		}
		else if (recv_[0] == 'o') {
			notification = "Game Start";
		}
		else if (recv_[0] == '\0')
			notification = "No people.";
		text->setText(notification);
	}
}

void Room::PlayTouch(cocos2d::Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		if ((gamecanbegin == 1 && !hasBeginRun) ||test_model == true) {
			hasBeginRun = true;
			auto director = Director::getInstance();
			//transfer to MapScene
			auto scene = MapOfGame::createScene();
			auto transition = TransitionCrossFade::create(1.0f, scene);
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			director->pushScene(transition);
		}
		break;
	}
}

void Room::BackTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		//transfer to MapScene
		auto scene = Hall::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->pushScene(transition);

		break;
	}
}

void Room::m_checkBoxCallback1(cocos2d::Ref * ref, CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		m_checkbox2->setSelectedState(false);
		m_checkbox3->setSelectedState(false);
		m_thumbnail = ImageView::create("RoomScene/map1.png");
		m_thumbnail->setAnchorPoint(Vec2(0, 0));
		m_thumbnail->setPosition(ccp(0, 0));
		m_blank->addChild(m_thumbnail);
		map_tag = 1;
		myMapSelect = 1;
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		myMapSelect = 0;
		break;
	default:
		break;
	}
}

void Room::m_checkBoxCallback2(cocos2d::Ref * ref, CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		m_checkbox1->setSelectedState(false);
		m_checkbox3->setSelectedState(false);
		m_thumbnail = ImageView::create("RoomScene/map2.png");
		m_thumbnail->setAnchorPoint(Vec2(0, 0));
		m_thumbnail->setPosition(ccp(0, 0));
		m_blank->addChild(m_thumbnail);
		map_tag = 2;
		myMapSelect = 2;
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		myMapSelect = 0;
		break;
	default:
		break;
	}
}

void Room::m_checkBoxCallback3(cocos2d::Ref * ref, CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		m_checkbox1->setSelectedState(false);
		m_checkbox2->setSelectedState(false);
		m_thumbnail = ImageView::create("RoomScene/map3.png");
		m_thumbnail->setAnchorPoint(Vec2(0, 0));
		m_thumbnail->setPosition(ccp(0, 0));
		m_blank->addChild(m_thumbnail);
		map_tag = 3;
		myMapSelect = 3;
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		myMapSelect = 0;
		break;
	default:
		break;
	}
}

void Room::r_checkBoxCallback1(cocos2d::Ref * ref, CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		r_checkbox2->setSelectedState(false);
		r_thumbnail = ImageView::create("RoomScene/face01.png");
		r_thumbnail->setAnchorPoint(Vec2(0.5, 0.5));
		r_blank->removeAllChildren();
		r_blank->addChild(r_thumbnail);
		r_thumbnail->setPosition(ccp(75, 65));
		role_tag = 1;
		myRoleSelect = 1;
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		myRoleSelect = 0;
		break;
	default:
		break;
	}
}

void Room::r_checkBoxCallback2(cocos2d::Ref * ref, CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		r_checkbox1->setSelectedState(false);
		r_thumbnail = ImageView::create("RoomScene/face03.png");
		r_thumbnail->setAnchorPoint(Vec2(0.5, 0.5));
		r_thumbnail->setPosition(ccp(75, 65));
		r_blank->removeAllChildren();
		r_blank->addChild(r_thumbnail);
		role_tag = 2;
		myRoleSelect = 2;
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		myRoleSelect = 0;
		break;
	default:
		break;
	}
}

void Room::onEnter() {
	Layer::onEnter();
}

void Room::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Room.mp3", true);
}

void Room::onExit() {
	Layer::onExit();
}

void Room::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
}

void Room::cleanup() {
	Layer::cleanup();
}
