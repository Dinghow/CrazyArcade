#include "PlayScene.h"
#include "../Login/LoginScene.h"
#include "Data.h"
#include "CoordTransfer.h"

cocos2d::CCTMXTiledMap* theMap;

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
		gameMap = CCTMXTiledMap::create("MapScene/map1/map1.tmx");
		break;
		break;
	}
	gameMap->setAnchorPoint(Vec2(0, 0));
	map_vehicle->addChild(gameMap);
	theMap = gameMap;
	//get objects layer
	CCTMXObjectGroup *objects = gameMap->objectGroupNamed("objects");
	CCTMXLayer *architecture = gameMap->layerNamed("architecture-real");
	architecture->setZOrder(1);
	CCTMXLayer *floatlayer = gameMap->layerNamed("architecture-float");
	floatlayer->setZOrder(888);
	CCAssert(objects != NULL, "ObjectLayer not found");

	//load the plist file and init the role
	cache = SpriteFrameCache::getInstance();
	role1.roleInit(objects, cache, 1);
	role2.roleInit(objects, cache, 2);
	gameMap->addChild(role1.role, 2);
	gameMap->addChild(role2.role, 2);
	m_Roles[0] = &role1;
	m_Roles[1] = &role2;

	//create the animation of four direction
	for (int i = 0; i < kTotal; i++) {
		walkAnimations[i] = creatAnimationByDirecton((RoleDirection)i,cache);
	}
	
	//bomb init
	for (int i = 0; i < 2; i++)
	{
		for (auto it : m_Roles[i]->m_Bombs)
		{
			it->getMap(gameMap);
			it->getRole(m_Roles[i]->role);
		}
	}

	//add keyboard listener
	auto listener = EventListenerKeyboard::create();
	//call responding animation when realted key is pressed
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
		keys[keyCode] = true;
		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			role1.playerInfo.isUpPressed = true;
			if (!role1.killedOrNot())
				keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			role1.playerInfo.isDownPressed = true;
			if (!role1.killedOrNot())
				keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			role1.playerInfo.isLeftPressed = true;
			if (!role1.killedOrNot())
				keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			role1.playerInfo.isRightPressed = true;
			if (!role1.killedOrNot())
				keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			role1.playerInfo.isSpacePressed = true;
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
				if (empty) {
					role1.dropBomb();
				}
			}
			break;
			//role2
		case EventKeyboard::KeyCode::KEY_ENTER:
			role2.playerInfo.isSpacePressed = true;
			if (!role2.killedOrNot())
			{
				bool empty = true;
				auto roleTileCoord = tilecoordForPosition(role2.role->getPosition());
				for (auto it : role2.m_Bombs)
				{
					if (it->droppedOrNot())
						if (roleTileCoord == tilecoordForPosition(it->bombOpenglCoord()))
						{
							empty = false;
							break;
						}
				}
				if (empty) {
					role2.dropBomb();
				}
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
			role1.playerInfo.isUpPressed = false;
			if (!role1.killedOrNot())
			{
				role1.role->stopAction(animations[kUp]);
				onWalkDone(kUp);
			}
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			role1.playerInfo.isDownPressed = false;
			if (!role1.killedOrNot()) 
			{
				role1.role->stopAction(animations[kDown]);
				onWalkDone(kDown);
			}
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			role1.playerInfo.isLeftPressed = false;
			if (!role1.killedOrNot()) 
			{
				role1.role->stopAction(animations[kLeft]);
				onWalkDone(kLeft);
			}
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			role1.playerInfo.isRightPressed = false;
			if (!role1.killedOrNot())
			{
				role1.role->stopAction(animations[kRight]);
				onWalkDone(kRight);
			}
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			role1.playerInfo.isSpacePressed = false;
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

	bombForcedDetonate();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			bombKillCheck(m_Roles[i], m_Roles[j]->m_Bombs);
			detonateKill(m_Roles[i], m_Roles[j]);
		}
		killRole(m_Roles[i]);
	}

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
	SimpleAudioEngine::getInstance()->playEffect("MusicSource/start.wav");
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
void MapOfGame::bombKillCheck(Player* role,vector<cBomb*>& vcBombs)
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
			if (rolePosition == ccpAdd(bombPosition, ccp(0, -i))&&i<=it->m_Board[0])
			{
				role->getKilled();
				break;
			}
			if (rolePosition == ccpAdd(bombPosition, ccp(i,0)) && i <= it->m_Board[1])
			{
				role->getKilled();
				break;
			}
			if (rolePosition == ccpAdd(bombPosition, ccp(0,i)) && i <= it->m_Board[2])
			{
				role->getKilled();
				break;
			}
			if (rolePosition == ccpAdd(bombPosition, ccp(-i,0)) && i <= it->m_Board[3])
			{
				role->getKilled();
				break;
			}
		}
	}
}

void MapOfGame :: killRole(Player* role)
{
	if (role->killedOrNot()&&!role->dyingOrNot()&&!role->deletedOrNot())
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

void MapOfGame::bombForcedDetonate()
{
	CCPoint bombPosition, forcedPosition;
	for (int i = 0; i < 2; i++)
	{
		for (auto it : m_Roles[i]->m_Bombs)
		{
			if (it->explodedOrNot())
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						for (auto forced : m_Roles[j]->m_Bombs)
						{
							if (it != forced&&forced->droppedOrNot() && !forced->explodedOrNot())
							{
								for (int j = 1; j <= it->m_Board[i]; j++)
								{
									bombPosition = ccpAdd(tilecoordForPosition(it->showBombPosition()), j*it->points[i]);
									forcedPosition = tilecoordForPosition(forced->showBombPosition());
									if (forcedPosition == bombPosition)
										forced->detonate();
								}
							}
						}
					}
				}
			}
		}
	}
}

void MapOfGame::detonateKill(Player* role1, Player* role2)
{
	if (role1->dyingOrNot() && !role1->deletedOrNot() && !role2->killedOrNot())
	{
		if (tilecoordForPosition(role1->role->getPosition()) == tilecoordForPosition(role2->role->getPosition()))
			role1->detonateKill();
	}
}