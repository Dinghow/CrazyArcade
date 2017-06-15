#include "PlayScene.h"
#include "../Login/LoginScene.h"
#include "HallScene.h"
#include "Data.h"
#include "CoordTransfer.h"

cocos2d::CCTMXTiledMap* theMap;
Player* m_Roles[2];

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
	seconds = 0;
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
	role1.roleInit(objects, cache, 1,role_tag,false);
	role2.roleInit(objects, cache, 2,2,true);
	gameMap->addChild(role1.role, 3);
	gameMap->addChild(role2.role, 3);
	m_Roles[0] = &role1;
	m_Roles[1] = &role2;
	opponent = 1;

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
				role1.keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			role1.playerInfo.isDownPressed = true;
			if (!role1.killedOrNot())
				role1.keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			role1.playerInfo.isLeftPressed = true;
			if (!role1.killedOrNot())
				role1.keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			role1.playerInfo.isRightPressed = true;
			if (!role1.killedOrNot())
				role1.keyPressedAnimation(keyCode);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			if (test_model == false) {
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
			}
			else if (test_model == true) {
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
			}
			break;
			//role2
		case EventKeyboard::KeyCode::KEY_KP_ENTER:
			if (test_model == true) {
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
			}
			break;
		case EventKeyboard::KeyCode::KEY_W:
			if(test_model == true){
			role2.playerInfo.isUpPressed = true;
			if (!role2.killedOrNot())
				role2.keyPressedAnimation(EventKeyboard::KeyCode::KEY_UP_ARROW);
			}
			break;
		case EventKeyboard::KeyCode::KEY_S:
			if (test_model == true) {
				role2.playerInfo.isDownPressed = true;
				if (!role2.killedOrNot())
					role2.keyPressedAnimation(EventKeyboard::KeyCode::KEY_DOWN_ARROW);
			}
			break;
		case EventKeyboard::KeyCode::KEY_A:
			if (test_model == true) {
				role2.playerInfo.isLeftPressed = true;
				if (!role2.killedOrNot())
					role2.keyPressedAnimation(EventKeyboard::KeyCode::KEY_LEFT_ARROW);
			}
			break;
		case EventKeyboard::KeyCode::KEY_D:
			if (test_model == true) {
				role2.playerInfo.isRightPressed = true;
				if (!role2.killedOrNot())
					role2.keyPressedAnimation(EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
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
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			role1.playerInfo.isUpPressed = false;
			if (!role1.killedOrNot())
			{
				role1.role->stopAction(role1.animations[kUp]);
				role1.onWalkDone(kUp);
			}
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			role1.playerInfo.isDownPressed = false;
			if (!role1.killedOrNot())
			{
				role1.role->stopAction(role1.animations[kDown]);
				role1.onWalkDone(kDown);
			}
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			role1.playerInfo.isLeftPressed = false;
			if (!role1.killedOrNot())
			{
				role1.role->stopAction(role1.animations[kLeft]);
				role1.onWalkDone(kLeft);
			}
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			role1.playerInfo.isRightPressed = false;
			if (!role1.killedOrNot())
			{
				role1.role->stopAction(role1.animations[kRight]);
				role1.onWalkDone(kRight);
			}
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			if (test_model == false) {
				role1.playerInfo.isSpacePressed = false;
			}
			else if (test_model == true) {
				role2.playerInfo.isSpacePressed = false;
			}
			break;
		case EventKeyboard::KeyCode::KEY_W:
			if (test_model == true) {
				role2.playerInfo.isUpPressed = false;
				if (!role2.killedOrNot())
				{
					role2.role->stopAction(role2.animations[kUp]);
					role2.onWalkDone(kUp);
				}
			}
			break;
		case EventKeyboard::KeyCode::KEY_S:
			if (test_model == true) {
				role2.playerInfo.isUpPressed = false;
				if (!role2.killedOrNot())
				{
					role2.role->stopAction(role2.animations[kDown]);
					role2.onWalkDone(kDown);
				}
			}
				break;
		case EventKeyboard::KeyCode::KEY_A:
			if (test_model == true) {
				role2.playerInfo.isUpPressed = false;
				if (!role2.killedOrNot())
				{
					role2.role->stopAction(role2.animations[kLeft]);
					role2.onWalkDone(kLeft);
				}
			}
				break;
		case EventKeyboard::KeyCode::KEY_D:
			if (test_model == true) {
				role2.playerInfo.isUpPressed = false;
				if (!role2.killedOrNot())
				{
					role2.role->stopAction(role2.animations[kRight]);
					role2.onWalkDone(kRight);
				}
			}
				break;
		case EventKeyboard::KeyCode::KEY_KP_ENTER:
			if (test_model == true) {
				role2.playerInfo.isSpacePressed = false;
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

	this->schedule(schedule_selector(MapOfGame::update), 0.05f);
	this->schedule(schedule_selector(MapOfGame::timer), 1.0f);
	return true;
}


MapOfGame::~MapOfGame() {
	this->unscheduleAllSelectors();
}

//count the time
void MapOfGame::timer(float delta) {
	seconds += delta;
	int temp = 180 - seconds;
	strstream ss;
	string s;
	ss << temp;
	ss >> s;
	if (seconds > 1)
		this->removeChild(numberAtlas);
	numberAtlas = CCLabelAtlas::create("0123456789", "MapScene/number.png", 12, 10, '0');
	numberAtlas->setPosition(ccp(720, 548));
	numberAtlas->setString(s);
	this->addChild(numberAtlas);
	if(seconds >= 180 && seconds < 181)
		judgeResult(false);
}
//control the role's behavior
void MapOfGame::update(float delta) {
	Node::update(delta);
	role1.loadPositon();
	role2.loadPositon();
	auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
		downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		w = EventKeyboard::KeyCode::KEY_W,
		s = EventKeyboard::KeyCode::KEY_S,
		a = EventKeyboard::KeyCode::KEY_A,
		d = EventKeyboard::KeyCode::KEY_D;
		

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
			role1.keyPressedMovement(upArrow);
		}
		else if (isKeyPressed(downArrow)) {
			role1.keyPressedMovement(downArrow);
		}
		else if (isKeyPressed(leftArrow)) {
			role1.keyPressedMovement(leftArrow);
		}
		else if (isKeyPressed(rightArrow)) {
			role1.keyPressedMovement(rightArrow);
		}
	}

	if (!role2.deletedOrNot() && test_model == true) {
		if (isKeyPressed(w)) {
			role2.keyPressedMovement(upArrow);
		}
		else if (isKeyPressed(s)) {
			role2.keyPressedMovement(downArrow);
		}
		else if (isKeyPressed(a)) {
			role2.keyPressedMovement(leftArrow);
		}
		else if (isKeyPressed(d)) {
			role2.keyPressedMovement(rightArrow);
		}
	}

	//Pick up items
	auto tilePosition1 = tilecoordForPosition(role1.getPosition());
	auto tilePosition2 = tilecoordForPosition(role2.getPosition());
	role1.pickUpItem(tilePosition1);
	role2.pickUpItem(tilePosition2);

	//result judge
	if (opponent == 0 && isMeAlive == true && !hasJudgeRun) {
		judgeResult(true);
	}
	if (opponent > 0 && isMeAlive == false && !hasJudgeRun) {
		judgeResult(false);
	}
	if (shouldBack == true && !hasBackRun)
		backToHall();

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

void MapOfGame::backToHall() {
	hasBackRun = true;
	auto director = Director::getInstance();
	auto scene = Hall::createScene();
	auto transition = TransitionCrossFade::create(0.5f, scene);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Prepare.mp3", true);
	director->pushScene(transition);
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

void MapOfGame::judgeResult(bool isWin) {
	hasJudgeRun = true;
	auto layer = GameOver::create();
	playResultMusic();
	layer->setAnchorPoint(Vec2(0.5, 0.5));
	layer->setPosition(300, 300);
	this->addChild(layer);
}

void MapOfGame::playResultMusic() {
	if (test_model == false){
		if (opponent == 0 && isMeAlive == true)
			SimpleAudioEngine::getInstance()->playEffect("MusicSource/win.wav");
		else if (isMeAlive == false)
			SimpleAudioEngine::getInstance()->playEffect("MusicSource/lose.wav");
	}
	else if (test_model == true) {
		if ((opponent == 0 && isMeAlive == true)||(opponent > 0 && isMeAlive == false))
			SimpleAudioEngine::getInstance()->playEffect("MusicSource/win.wav");
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

void MapOfGame :: killRole(Player* player)
{
	if (player->killedOrNot()&&!player->dyingOrNot()&&!player->deletedOrNot())
	{
		/*if (keys[EventKeyboard::KeyCode::KEY_UP_ARROW])
			player->role->stopAction(player->animations[kUp]);
		if (keys[EventKeyboard::KeyCode::KEY_DOWN_ARROW])
			player->role->stopAction(player->animations[kDown]);
		if (keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
			player->role->stopAction(player->animations[kLeft]);
		if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
			player->role->stopAction(player->animations[kRight]);*/
		player->role->stopAllActions();
		if (!player->deletedOrNot())
		{
			if (!player->dyingOrNot())
			{
				player->setDying();
				player->setRoleDead();
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