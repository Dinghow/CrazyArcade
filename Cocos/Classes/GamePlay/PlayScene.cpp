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
	role1.startPosition = positionForTileCoord(CCPoint(startX, startY));
	//load the plist file
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("RoleSource/bazzi.plist");
	//create the animation of four direction
	for (int i = 0; i < kTotal; i++) {
		walkAnimations[i] = creatAnimationByDirecton((RoleDirection)i,cache);
	}

	//create the role and set the first frame as the static condition
	role1.role = Sprite::createWithSpriteFrameName("role/stop_down.png");
	role1.role->setAnchorPoint(Vec2(0, 0));
	role1.role->setPosition(ccp(startX,startY));
	map->addChild(role1.role,1);

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
CCAnimation* MapOfGame::creatAnimationByDirecton(RoleDirection direction, cocos2d::SpriteFrameCache* cache) {
	Vector<SpriteFrame*> frames(5);
	cocos2d::SpriteFrame* frame1, *frame2, *frame3, *frame4, *frame5;
	switch (direction)
	{
	case kUp:
		frame1 = cache->getSpriteFrameByName("role/stop_up.png");
		frame2 = cache->getSpriteFrameByName("role/move_up_1.png");
		frame3 = cache->getSpriteFrameByName("role/move_up_2.png");
		frame4 = cache->getSpriteFrameByName("role/move_up_3.png");
		frame5 = cache->getSpriteFrameByName("role/move_up_4.png");
		frames.pushBack(frame1);
		frames.pushBack(frame2);
		frames.pushBack(frame3);
		frames.pushBack(frame4);
		frames.pushBack(frame5);
		break;
		/*animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_up.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_4.png"));
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);*/
	case kDown:
		frame1 = cache->getSpriteFrameByName("role/stop_down.png");
		frame2 = cache->getSpriteFrameByName("role/move_down_1.png");
		frame3 = cache->getSpriteFrameByName("role/move_down_2.png");
		frame4 = cache->getSpriteFrameByName("role/move_down_3.png");
		frame5 = cache->getSpriteFrameByName("role/move_down_4.png");
		frames.pushBack(frame1);
		frames.pushBack(frame2);
		frames.pushBack(frame3);
		frames.pushBack(frame4);
		frames.pushBack(frame5);
		break;
		/*animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_down.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_4.png"));
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);*/
	case kLeft:
		frame1 = cache->getSpriteFrameByName("role/stop_left.png");
		frame2 = cache->getSpriteFrameByName("role/move_left_1.png");
		frame3 = cache->getSpriteFrameByName("role/move_left_2.png");
		frame4 = cache->getSpriteFrameByName("role/move_left_3.png");
		frame5 = cache->getSpriteFrameByName("role/move_left_4.png");
		frames.pushBack(frame1);
		frames.pushBack(frame2);
		frames.pushBack(frame3);
		frames.pushBack(frame4);
		frames.pushBack(frame5);
		break;
		/*animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_left.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_4.png"));
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);*/
	case kRight:
		frame1 = cache->getSpriteFrameByName("role/stop_right.png");
		frame2 = cache->getSpriteFrameByName("role/move_right_1.png");
		frame3 = cache->getSpriteFrameByName("role/move_right_2.png");
		frame4 = cache->getSpriteFrameByName("role/move_right_3.png");
		frame5 = cache->getSpriteFrameByName("role/move_right_4.png");
		frames.pushBack(frame1);
		frames.pushBack(frame2);
		frames.pushBack(frame3);
		frames.pushBack(frame4);
		frames.pushBack(frame5);
		break;
		/*animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_right.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_4.png"));
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);*/
	default:
		break;
	}
	CCAnimation* animation = new CCAnimation();
	animation->initWithSpriteFrames(frames, 0.2f);

	return animation;
}

//set face direciton
void MapOfGame::setFaceDirection(RoleDirection direction) {
	switch (direction) {
	case kUp:
		role1.role->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_up.png"));
		break;
	case kDown:
		role1.role->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_down.png"));
		break;
	case kLeft:
		role1.role->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_left.png"));
		break;
	case kRight:
		role1.role->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_right.png"));
		break;
	default:
		break;
	}
}

//the call back function of finished walk
void MapOfGame::onWalkDone(RoleDirection direction) {
	this->setFaceDirection(direction);
}

//transfer position coord to tile coord
CCPoint MapOfGame::tilecoordForPosition(CCPoint position) {
	int x = int(position.x / map->getTileSize().width);
	int y = int((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return ccp(x, y);
}

//transfer tile coord to postion coord
CCPoint MapOfGame::positionForTileCoord(CCPoint position) {
	float x = float(position.x*map->getTileSize().width);
	float y = float((map->getMapSize().height*map->getTileSize().height)-position.y*map->getTileSize().height);
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
	/*if (map->layerNamed("wall")->tileGIDAt(tileCoord)) {
		return kWall;
	}*/
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
void MapOfGame::keyPressedAnimation(EventKeyboard::KeyCode keyCode) {
	RoleDirection tag;
	//you can set move speed here
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		tag = kUp;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		tag = kDown;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		tag = kLeft;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		tag = kRight;
		break;
	default:
		break;
	}
	animations[tag] = RepeatForever::create(CCAnimate::create(walkAnimations[tag]));
	//animations[tag] = CCAnimate::create(walkAnimations[tag]);
	role1.role->runAction(animations[tag]);
}

void MapOfGame::keyPressedMovement(EventKeyboard::KeyCode keyCode) {
	CCPoint moveByPosition;
	RoleDirection tag;
	//you can set move speed here
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		moveByPosition = ccp(0, role1.getSpeed());
		tag = kUp;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		moveByPosition = ccp(0, -role1.getSpeed());
		tag = kDown;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		moveByPosition = ccp(-role1.getSpeed(), 0);
		tag = kLeft;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveByPosition = ccp(role1.getSpeed(), 0);
		tag = kRight;
		break;
	default:
		moveByPosition = ccp(0, 0);
		break;
	}
	//collision check
	CCPoint targetPosition = ccpAdd(role1.role->getPosition(), moveByPosition);
	if (checkCollision(targetPosition) == kWall) {
		setFaceDirection(tag);
		return;
	}
	//create a action combined move action and related animation
	/*CCAction *action = CCSequence::create(
		CCSpawn::create(
			CCAnimate::create(walkAnimations[tag]),
			CCMoveBy::create(0.28f, moveByPosition), NULL)
		,CCCallFuncND::create(this, callfuncND_selector(MapOfGame::onWalkDone), (void*)(tag))
		, NULL);*/
	//auto spaw = CCSpawn::create(CCAnimate::create(walkAnimations[tag]), CCMoveBy::create(0.01f, moveByPosition), NULL);
	auto move = CCMoveBy::create(0.28f, moveByPosition);
	role1.role->runAction(move);
}