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

	//add cursor
	auto cursor = Sprite::create("cursor_nor.png");
	this->_cursor = Node::create();
	this->_cursor->addChild(cursor);
	this->addChild(this->_cursor, 10000);

	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseMove = [&](cocos2d::EventMouse* event) {
		Point mouse = event->getLocation();
		mouse.y = 600 - mouse.y;

		this->_cursor->setPosition(Point(mouse.x + 20, mouse.y - 30));
	};
	listenerMouse->onMouseDown = [&](cocos2d::EventMouse* event) {
		this->_cursor->removeAllChildren();
		auto cursor = Sprite::create("cursor_pre.png");
		this->_cursor->addChild(cursor);
	};
	listenerMouse->onMouseUp = [&](cocos2d::EventMouse* event) {
		this->_cursor->removeAllChildren();
		auto cursor = Sprite::create("cursor_nor.png");
		this->_cursor->addChild(cursor);
	};
	this->_eventDispatcher->addEventListenerWithFixedPriority(listenerMouse, 1);

	return true;
}

void AboutUs::ReturnMenuTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto scene = MenuTable::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->pushScene(transition);

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