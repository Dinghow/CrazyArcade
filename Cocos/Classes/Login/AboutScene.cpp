#include "MenuScene.h"
#include "AboutScene.h"

Scene* AboutUs::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = AboutUs::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool AboutUs::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//*****ATTENTION******the name of button must use lower case
	auto rootNode = CSLoader::createNode("AboutUsScene/AboutScene.csb");
	Layout* background = (Layout*)rootNode->getChildByName("background");
	Button* btnReturnMainMenu = (Button*)Helper::seekWidgetByName(background, "returnbutton");


	btnReturnMainMenu->addTouchEventListener(CC_CALLBACK_2(AboutUs::ReturnMenuTouch, this));

	addChild(rootNode);

	return true;
}

void AboutUs::ReturnMenuTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		director->popScene();

		break;
	}
}

void AboutUs::onEnter() {
	Layer::onEnter();
}

void AboutUs::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
}

void AboutUs::onExit() {
	Layer::onExit();
}

void AboutUs::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
}

void AboutUs::cleanup() {
	Layer::cleanup();
}