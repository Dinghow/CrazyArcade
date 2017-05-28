#include "PlayScene.h"

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
	CCTMXLayer *architecture = map->layerNamed("architecture");
	architecture->setZOrder(1);
	CCAssert(objects != NULL, "ObjectLayer not found");
	//set first spawn point
	auto spawnPoint1 = objects->objectNamed("spawnpoint1");
	int startX = spawnPoint1.at("x").asInt();
	int startY = spawnPoint1.at("y").asInt();

	//load the plist file
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("RoleSource/bazzi.plist");
	//create the animation of four direction
	/*for (int i = 0; i < kTotal; i++) {
		walkAnimations[i] = creatAnimationByDirecton((RoleDirection)i);
	}*/

	//create the role and set the first frame as the static condition
	role1 = Sprite::createWithSpriteFrameName("role/stop_down.png");
	role1->setAnchorPoint(Vec2(0, 0));
	role1->setPosition(ccp(startX,startY));
	map->addChild(role1,1);

	//add keyboard listener
	auto listener = EventListenerKeyboard::create();
	//set the corresponding key map to bool value
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
		keys[keyCode] = true;
	};	
	
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event *event) {
		keys[keyCode] = false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//call the schedule
	this->scheduleUpdate();

	return true;
}

//set close menu
/*void MapOfGame::menuCloseCallback(CCObject *pSender) {
	//"close" menu item clicked
	CCDirector::sharedDirector()->end();
}*/


//create animation frames
CCAnimation* MapOfGame::creatAnimationByDirecton(RoleDirection direction) {
	CCAnimation *animation = Animation::create();
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("RoleSource/bazzi.plist");
	switch (direction)
	{
	case kUp:
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_up.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_4.png"));
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(false);
	case kDown:
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_down.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_4.png"));
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);
	case kLeft:
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_left.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_4.png"));
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);
	case kRight:
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_right.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_4.png"));
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);
	default:
		break;
	}
	return animation;
}

//set the call back function 
/*void MapOfGame::menuCallbackMove(CCObject *pSender) {
	if (this->isRoleWalking)
		return;
	CCNode* node = (CCNode*)pSender;
	RoleDirection tag = (RoleDirection)node->getTag();
	CCPoint moveByPosition;
	switch (tag) {
	case kUp:
		moveByPosition = ccp(0, 20);
	case kDown:
		moveByPosition = ccp(0, -20);
	case kLeft:
		moveByPosition = ccp(-20, 0);
	case kRight:
		moveByPosition = ccp(20, 0);
		break;
	}
	CCPoint targetPosition = ccpAdd(role1->getPosition(), moveByPosition);
	//collision check
	if (checkCollision(targetPosition) == kWall) {
		setFaceDirection(tag);
		return;
	}
	/*CCAction *action = CCSequence::create(
		CCSpawn::create(
			CCAnimate::create(walkAnimations[tag]),
			CCMoveBy::create(0.28f, moveByPosition), NULL),								    
		CCCallFuncND::create(this, callfuncND_selector(MapOfGame::onWalkDone), (void*)(tag)), NULL);
	
	role1->runAction(action);
}*/

//set face direciton
void MapOfGame::setFaceDirection(RoleDirection direction) {
	switch (direction) {
	case kUp:
		role1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_up.png"));
	case kDown:
		role1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_down.png"));
	case kLeft:
		role1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_down.png"));
	case kRight:
		role1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_down.png"));
		break;
	}
}

//the call back function of finished walk
void MapOfGame::onWalkDone(CCNode *pTarget, void *data) {
	RoleDirection direction = (RoleDirection)(int)data;
	this->setFaceDirection(direction);
}

//coord transfer
CCPoint MapOfGame::tilecoordForPosition(CCPoint position) {
	int x = int(position.x / map->getTileSize().width);
	int y = int(position.y / map->getTileSize().height);
	return ccp(x, y);
}

CCPoint MapOfGame::positionForTileCoord(CCPoint position) {
	float x = float(position.x*map->getTileSize().width);
	float y = float(position.y*map->getTileSize().height);
	return ccp(x, y);
}

//collision check according to the role's position
MapOfGame::CollisionType MapOfGame::checkCollision(cocos2d::CCPoint rolePosition) {
	//transfer the coord
	CCPoint tileCoord = tilecoordForPosition(rolePosition);
	//check the border of map
	if (tileCoord.x<0 || tileCoord.x>map->getMapSize().width - 1 || tileCoord.y<0 || tileCoord.y>map->getMapSize().height - 1) {
		return kWall;
	}
	if (map->layerNamed("wall")->tileGIDAt(tileCoord)) {
		return kWall;
	}
	else {
		return kNone;
	}
}

MapOfGame::~MapOfGame() {
	for (int i = 0; i < 4; i++) {
		CC_SAFE_RELEASE(walkAnimations[i]);
	}
	this->unscheduleAllSelectors();
}

//transfer keyboardevent in update 
void MapOfGame::update(float delta) {
	Node::update(delta);
	auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
		downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	if (isKeyPressed(upArrow)) {
		keyPressedEvent(upArrow);
	}
	else if (isKeyPressed(downArrow)) {
		keyPressedEvent(downArrow);
	}
	else if (isKeyPressed(leftArrow)) {
		keyPressedEvent(leftArrow);
	}
	else if (isKeyPressed(rightArrow)) {
		keyPressedEvent(rightArrow);
	}
}

//check whether the key is pressed
bool MapOfGame::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

//the event during key pressed
void MapOfGame::keyPressedEvent(EventKeyboard::KeyCode keyCode) {
	CCPoint moveByPosition;
	RoleDirection tag;
	//you can set move speed here
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		moveByPosition = ccp(0, 2);
		tag = kUp;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		moveByPosition = ccp(0, -2);
		tag = kDown;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		moveByPosition = ccp(-2, 0);
		tag = kLeft;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveByPosition = ccp(2, 0);
		tag = kRight;
		break;
	default:
		moveByPosition = ccp(0, 0);
		break;
	}
	CCPoint targetPosition = ccpAdd(role1->getPosition(), moveByPosition);
	
	//create a action combined move action and related animation
	/*CCAction *action = CCSequence::create(
		CCSpawn::create(
			CCAnimate::create(walkAnimations[tag]),
			CCMoveBy::create(0.28f, moveByPosition), NULL),
		CCCallFuncND::create(this, callfuncND_selector(MapOfGame::onWalkDone), (void*)(tag)), NULL);*/
	auto move = CCMoveBy::create(0.28f, moveByPosition);

	role1->runAction(move);
}