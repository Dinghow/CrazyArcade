#include "PlayScene.h"
#include "../Login/LoginScene.h"

Scene* MapOfGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapOfGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MapOfGame::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("MapScene/Map.csb");
	this->addChild(rootNode);

	//get map from the csb
	map = (CCTMXTiledMap *)rootNode->getChildByName("map");

	//get objects layer
	CCTMXObjectGroup *objects = map->objectGroupNamed("objects");
	CCTMXLayer *architecture = map->layerNamed("architecture-real");
	architecture->setZOrder(1);
	CCTMXLayer *floatlayer = map->layerNamed("architecture-float");
	floatlayer->setZOrder(888);
	CCAssert(objects != NULL, "ObjectLayer not found");

	//set first spawn point
	auto spawnPoint1 = objects->objectNamed("spawnpoint1");
	int startX = spawnPoint1.at("x").asInt();
	int startY = spawnPoint1.at("y").asInt();
	role1.startPosition = tilecoordForPosition(CCPoint(startX, startY));

	//load the plist file
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("RoleSource/bazzi.plist");

	//create the animation of four direction
	for (int i = 0; i < kTotal; i++) {
		walkAnimations[i] = creatAnimationByDirecton((RoleDirection)i,cache);
	}

	//create the role and set the first frame as the static condition
	role1.role = Sprite::createWithSpriteFrameName("role/stop_down.png");
	role1.role->setAnchorPoint(Vec2(0.5,0.5));
	role1.role->setPosition(ccp(startX+20,startY+28));
	//add shadow for the role
	role1.shadow = Sprite::create("Role/shadow.png");
	role1.shadow->setAnchorPoint(Vec2(0.45, 0.6));
	role1.shadow->setPosition(role1.role->getPosition());
	role1.role->addChild(role1.shadow);
	role1.shadow->setLocalZOrder(-1);
	
	map->addChild(role1.role,2);


	//add keyboard listener
	auto listener = EventListenerKeyboard::create();
	//call responding animation when realted key is pressed
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
		keys[keyCode] = true;
		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			keyPressedAnimation(keyCode);
			break;
		default:
			break;
	}
};	
	//call stop event when related key is released
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event *event) {
		keys[keyCode] = false;
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW :
			role1.role->stopAction(animations[kUp]);
			onWalkDone(kUp);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			role1.role->stopAction(animations[kDown]);
			onWalkDone(kDown);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			role1.role->stopAction(animations[kLeft]);
			onWalkDone(kLeft);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			role1.role->stopAction(animations[kRight]);
			onWalkDone(kRight);
			break;
		default:
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//set exit button
	Button* btnBackMain = (Button*)rootNode->getChildByName("exitbutton");
	btnBackMain->addTouchEventListener(CC_CALLBACK_2(MapOfGame::BackTouch, this));
	//call the schedule
//*******ATTENTION:the duration of schedule must large than that of move action,if not there'll be collision check bug***********//
	this->schedule(schedule_selector(MapOfGame::update), 0.05f);

	return true;
}

//set close menu
/*void MapOfGame::menuCloseCallback(CCObject *pSender) {
	//"close" menu item clicked
	CCDirector::sharedDirector()->end();
}*/

//transfer position coord to tile coord
CCPoint MapOfGame::tilecoordForPosition(CCPoint position) {
	int x = 0;
	int y = 0;
	if (position.x > 0)
		x = int(position.x / map->getTileSize().width);
	else if (position.x < 0)
		x = -1;
	if (position.y > 0)
		y = map->getMapSize().height - 1 - int(position.y / map->getTileSize().height);
	else if (position.y < 0)
		y = -1;
	return ccp(x, y);
}

//transfer tile coord to postion coord
CCPoint MapOfGame::positionForTileCoord(CCPoint position) {
	float x = float(position.x*map->getTileSize().width);
	float y = float(((map->getMapSize().height-1)*map->getTileSize().height)-position.y*map->getTileSize().height);
	return ccp(x, y);
}


MapOfGame::~MapOfGame() {
	for (int i = 0; i < 4; i++) {
		CC_SAFE_RELEASE(walkAnimations[i]);
		CC_SAFE_RELEASE(animations[i]);
	}
	this->unscheduleAllSelectors();
}

//control the role's behavior
void MapOfGame::update(float delta) {
	Node::update(delta);
	role1.loadPositon();
	auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
		downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	if (isKeyPressed(upArrow)) {
		keyPressedMovement(upArrow);
	}
	else if (isKeyPressed(downArrow)) {
		keyPressedMovement(downArrow);
	}
	else if (isKeyPressed(leftArrow)) {
		keyPressedMovement(leftArrow);
	}
	else if (isKeyPressed(rightArrow)) {
		keyPressedMovement(rightArrow);
	}
}

void MapOfGame::BackTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto scene = Login::createScene();
		auto transition = TransitionCrossFade::create(0.5f, scene);
		director->replaceScene(transition);
		break;
	}
}