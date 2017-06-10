#include "PlayScene.h"
#include "../Login/LoginScene.h"
#include "Data.h"

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
	Layout* map_vehicle = (Layout*)rootNode->getChildByName("map_vehicle");
	this->addChild(rootNode);
	
	//select map
	switch (map_tag)
	{
	case 1:
		gameMap = CCTMXTiledMap::create("MapScene/map1/map1.tmx");
		break;
	case 2:
		gameMap = CCTMXTiledMap::create("MapScene/map2/map2.tmx");
		break;
	case 3:
		gameMap = CCTMXTiledMap::create("MapScene/map3/map3.tmx");
		break;
	default:
		break;
	}
	gameMap->setAnchorPoint(Vec2(0, 0));
	map_vehicle->addChild(gameMap);
	//get objects layer
	CCTMXObjectGroup *objects = gameMap->objectGroupNamed("objects");
	CCTMXLayer *architecture = gameMap->layerNamed("architecture-real");
	architecture->setZOrder(1);
	CCTMXLayer *floatlayer = gameMap->layerNamed("architecture-float");
	floatlayer->setZOrder(888);
	CCAssert(objects != NULL, "ObjectLayer not found");

	//set first spawn point
	auto spawnPoint1 = objects->objectNamed("spawnpoint1");
	int startX = spawnPoint1.at("x").asInt();
	int startY = spawnPoint1.at("y").asInt();
	role1.startPosition = tilecoordForPosition(CCPoint(startX, startY));

	//load the plist file
	cache = SpriteFrameCache::getInstance();
	switch (role_tag)
	{
	case 1:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("RoleSource/bazzi.plist");
<<<<<<< HEAD
		role1.setProperties(6.5, 1, 1);
=======
		role1.setProperties(6.5, 5, 1);
>>>>>>> origin/hpc
		break;
	case 2:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("RoleSource/cappi.plist");
		role1.setProperties(6.0, 1.2, 1);
		break;
	default:
		break;
	}

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
	role1.shadow->setAnchorPoint(Vec2(0,0));
	role1.shadow->setPosition(ccp(0,0));
	role1.role->addChild(role1.shadow);
	role1.shadow->setLocalZOrder(-1);
	
	gameMap->addChild(role1.role,2);
	
	//bomb init
	for (auto it : role1.m_Bombs)
	{
		it->getMap(gameMap);
		it->getRole(role1.role);
	}

	//add keyboard listener
	auto listener = EventListenerKeyboard::create();
	//call responding animation when realted key is pressed
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
		keys[keyCode] = true;
		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			if (!role1.killedOrNot())
				keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			if (!role1.killedOrNot())
				keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			if (!role1.killedOrNot())
				keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			if (!role1.killedOrNot())
				keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			if (!role1.killedOrNot())
			{
				bool empty = true;
				auto roleTileCoord = tilecoordForPosition(role1.role->getPosition());
				for (auto it : role1.m_Bombs)
				{
					if (it->droppedOrNot())
						if (roleTileCoord == tilecoordForPosition(it->bombOpenglCoord()))
						{
							empty = false;
							break;
						}
				}
				if (empty)
					role1.dropBomb();
			}
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
			if (!role1.killedOrNot())
			{
				role1.role->stopAction(animations[kUp]);
				onWalkDone(kUp);
			}
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			if (!role1.killedOrNot()) 
			{
				role1.role->stopAction(animations[kDown]);
				onWalkDone(kDown);
			}
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			if (!role1.killedOrNot()) 
			{
				role1.role->stopAction(animations[kLeft]);
				onWalkDone(kLeft);
			}
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			if (!role1.killedOrNot())
			{
				role1.role->stopAction(animations[kRight]);
				onWalkDone(kRight);
			}
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
	//this->scheduleOnce(schedule_selector(MapOfGame)
	this->schedule(schedule_selector(MapOfGame::update), 0.05f);
	//play background music via the schedule
	//this->scheduleOnce(schedule_selector(MapOfGame::playMusic), 0.5f);
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
		x = int(position.x / gameMap->getTileSize().width);
	else if (position.x < 0)
		x = -1;
	if (position.y > 0)
		y = gameMap->getMapSize().height - 1 - int(position.y / gameMap->getTileSize().height);
	else if (position.y < 0)
		y = -1;
	return ccp(x, y);
}

//transfer tile coord to postion coord
CCPoint MapOfGame::positionForTileCoord(CCPoint position) {
	float x = float(position.x*gameMap->getTileSize().width);
	float y = float(((gameMap->getMapSize().height-1)*gameMap->getTileSize().height)-position.y*gameMap->getTileSize().height);
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

	bombKillCheck(&role1, role1.m_Bombs);
	killRole(&role1);

	if (!role1.deletedOrNot())
	{
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

	//Pick up items
	auto tilePosition = tilecoordForPosition(role1.getPosition());
	role1.pickUpItem(tilePosition);
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

void MapOfGame::playMusic(float dt) {
	SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Village.mp3", true);
}

void MapOfGame::onEnter() {
	Layer::onEnter();
}

void MapOfGame::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	//play music
	SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Village.mp3", true);
	SimpleAudioEngine::getInstance()->playEffect("MusicSource/appear.wav");
}

void MapOfGame::onExit() {
	Layer::onExit();
}

void MapOfGame::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
}

void MapOfGame::cleanup() {
	Layer::cleanup();
}


/***************************************
*admitted by hpc                       *
*                                      *
*                                      *
*                                      *
*                                      *
*                                      *
****************************************/
void MapOfGame::bombKillCheck(Role* role,vector<cBomb*>& vcBombs)
{
	
	CCPoint rolePosition = tilecoordForPosition(role->role->getPosition());
	for (auto it : vcBombs)
	{
		if (!it->explodedOrNot())
			continue;
		CCPoint bombPosition = tilecoordForPosition(it->showBombPosition());
		if (bombPosition == rolePosition)
		{
			role->getKilled();
		}
		for (int i = 1; i <= role->showBombRange(); i++)
		{
<<<<<<< HEAD
			if (rolePosition == ccpAdd(bombPosition, ccp(0, -i)))
=======
			if (rolePosition == ccpAdd(bombPosition, ccp(0, -i))&&i<=it->m_Board[0])
>>>>>>> origin/hpc
			{
				role->getKilled();
				break;
			}
<<<<<<< HEAD
			if (rolePosition == ccpAdd(bombPosition, ccp(i,0)))
=======
			if (rolePosition == ccpAdd(bombPosition, ccp(i,0)) && i <= it->m_Board[1])
>>>>>>> origin/hpc
			{
				role->getKilled();
				break;
			}
<<<<<<< HEAD
			if (rolePosition == ccpAdd(bombPosition, ccp(0,i)))
=======
			if (rolePosition == ccpAdd(bombPosition, ccp(0,i)) && i <= it->m_Board[2])
>>>>>>> origin/hpc
			{
				role->getKilled();
				break;
			}
<<<<<<< HEAD
			if (rolePosition == ccpAdd(bombPosition, ccp(-i,0)))
=======
			if (rolePosition == ccpAdd(bombPosition, ccp(-i,0)) && i <= it->m_Board[3])
>>>>>>> origin/hpc
			{
				role->getKilled();
				break;
			}
		}
	}
}

void MapOfGame :: killRole(Role* role)
{

	if (role->killedOrNot())
	{
		if (keys[EventKeyboard::KeyCode::KEY_UP_ARROW])
			role->role->stopAction(animations[kUp]);
		if (keys[EventKeyboard::KeyCode::KEY_DOWN_ARROW])
			role->role->stopAction(animations[kDown]);
		if (keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
			role->role->stopAction(animations[kLeft]);
		if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
			role->role->stopAction(animations[kRight]);
		if (!role->deletedOrNot())
		{
			if (!role->dyingOrNot())
			{
				role->setDying();
				role->setRoleDead();
			}
		}
	}
}
