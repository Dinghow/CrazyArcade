#include "LoginScene.h"
#include "MenuScene.h"
#include "../GamePlay/PlayScene.h"

Scene* Login::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Login::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Login::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//get the csb file and the elements on it
	auto rootNode = CSLoader::createNode("LoginScene/LoginScene.csb");
	Layout* background = (Layout*)rootNode->getChildByName("background");
	Button* btnMenu = (Button*)Helper::seekWidgetByName(background, "menubutton");
	Button* btnStartGame = (Button*)Helper::seekWidgetByName(background, "playbutton");
	Button* btnExit = (Button*)Helper::seekWidgetByName(background, "exitbutton");

	//set touch event listener on the buttons 
	btnMenu->addTouchEventListener(CC_CALLBACK_2(Login::MenuTouch, this));
	btnStartGame->addTouchEventListener(CC_CALLBACK_2(Login::StartGameTouch, this));
	btnExit->addTouchEventListener(CC_CALLBACK_2(Login::ExitTouch, this));

	addChild(rootNode);

	return true;
}

//set the touch event after click menubutton
void Login::MenuTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//transfer to MenuScene
		auto director = Director::getInstance();
		auto scene = MenuTable::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(transition);

		break;
	}
}

//set the touch event after click playbutton
void Login::StartGameTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		//transfer to MapScene
		auto scene = MapOfGame::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(transition);

		break;
	}
}

//set the touch event after click exitbutton
void Login::ExitTouch(Ref* pSender, Widget::TouchEventType type) {
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
	#endif
}
