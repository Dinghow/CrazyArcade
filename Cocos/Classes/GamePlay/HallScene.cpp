#include "HallScene.h"
#include "Login/MenuScene.h"
#include "Login/LoginScene.h"
#include "PlayScene.h"
#include "RoomScene.h"
#include "Data.h"

Scene* Hall::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Hall::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Hall::init()
{
	if (!Layer::init())
	{
		return false;
	}
	test_model = false;
	auto rootNode = CSLoader::createNode("HallScene/HallScene.csb");
	Layout* background = (Layout*)rootNode->getChildByName("background");
	//get button and checkbox from the csb file
	Button* btnStartServer = (Button*)Helper::seekWidgetByName(background, "start_server");
	Button* btnConnectServer = (Button*)Helper::seekWidgetByName(background, "connect_server");
	Button* btnMenu = (Button*)Helper::seekWidgetByName(background, "menu");
	Button* btnExit = (Button*)Helper::seekWidgetByName(background, "exit");
	Button* btnBack = (Button*)Helper::seekWidgetByName(background, "back");
	Button* btnTest = (Button*)Helper::seekWidgetByName(background, "test");

	btnStartServer->addTouchEventListener(CC_CALLBACK_2(Hall::StartTouch, this));
	btnConnectServer->addTouchEventListener(CC_CALLBACK_2(Hall::ConnectTouch, this));
	btnMenu->addTouchEventListener(CC_CALLBACK_2(Hall::MenuTouch, this));
	btnExit->addTouchEventListener(CC_CALLBACK_2(Hall::ExitTouch, this));
	btnBack->addTouchEventListener(CC_CALLBACK_2(Hall::BackTouch, this));
	btnTest->addTouchEventListener(CC_CALLBACK_2(Hall::TestTouch, this));


	addChild(rootNode);

	return true;
}

void Hall::StartTouch(cocos2d::Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		/*auto director = Director::getInstance();
		//transfer to MapScene
		auto scene = Room::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		director->pushScene(transition);*/

		break;
	}
}

void Hall::ConnectTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	/*case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		//transfer to MapScene
		auto scene = Room::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->pushScene(transition);*/

		break;
	}
}

void Hall::TestTouch(cocos2d::Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		//transfer to MapScene
		test_model = true;
		auto scene = Room::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		director->pushScene(transition);

		break;
	}
}

void Hall::MenuTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		//transfer to MapScene
		auto scene = MenuTable::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->pushScene(transition);

		break;
	}
}

void Hall::ExitTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//Close the cocos2d-x game scene and quit the application
		Director::getInstance()->end();
		break;
	}
}

void Hall::BackTouch(Ref* pSender, Widget::TouchEventType type) {
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
