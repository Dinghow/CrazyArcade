#include "MenuScene.h"
#include "LoginScene.h"
#include "AboutScene.h"

Scene* MenuTable::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuTable::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuTable::init()
{
	/**  you can create scene with following comment code instead of using csb file.
	// 1. super init first
	if ( !Layer::init() )
	{
	return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuTableItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(MenuTable::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
	origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = MenuTable::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
	origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "MenuTable" splash screen"
	auto sprite = Sprite::create("MenuTable.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	**/

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	//*****ATTENTION******the name of button must use lower case
	auto rootNode = CSLoader::createNode("MenuScene/MenuScene.csb");
	Layout* background = (Layout*)rootNode->getChildByName("background");
	Button* btnReturnMainMenu = (Button*)Helper::seekWidgetByName(background, "returnbutton");
	Button* btnPlusVolume = (Button*)Helper::seekWidgetByName(background, "plus_button");
	Button* btnMinusVolume = (Button*)Helper::seekWidgetByName(background, "minus_button");
	Button* btnAbout = (Button*)Helper::seekWidgetByName(background, "about_button");
	

	btnReturnMainMenu->addTouchEventListener(CC_CALLBACK_2(MenuTable::ReturnMainTouch, this));
	btnAbout->addTouchEventListener(CC_CALLBACK_2(MenuTable::AboutTouch, this));
	btnPlusVolume->addTouchEventListener(CC_CALLBACK_2(MenuTable::PlusTouch, this));
	btnMinusVolume->addTouchEventListener(CC_CALLBACK_2(MenuTable::MinusTouch, this));

	addChild(rootNode);

	return true;
}

void MenuTable::ReturnMainTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto scene = Login::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(transition);

		break;
	}
}

void MenuTable::AboutTouch(cocos2d::Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto scene = AboutUs::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->pushScene(transition);

		break;
	}
}

void MenuTable::PlusTouch(cocos2d::Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() + 0.1f);
		break;
	}
}
void MenuTable::MinusTouch(cocos2d::Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() - 0.1f);
		break;
	}
}

void MenuTable::onEnter() {
	Layer::onEnter();
}

void MenuTable::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Xmas.mp3", true);
}

void MenuTable::onExit() {
	Layer::onExit();
}

void MenuTable::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
}

void MenuTable::cleanup() {
	Layer::cleanup();
}