#include "PlayScene.h"
#include "../Login/LoginScene.h"
#include "HallScene.h"
#include "Data.h"
#include "Item.h"
#include "../Connect/client.h"
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
	closeServer = false;
	seconds = 0;
	direction = kStart;
	direction2 = kStart;
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
	case 4:
		gameMap = CCTMXTiledMap::create("MapScene/map4/map4.tmx");
		break;
	case 5:
		gameMap = CCTMXTiledMap::create("MapScene/map5/map5.tmx");
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
	if (role_tag == 1 && test_model == false)
		isHost = true;
	role1.roleInit(objects, cache, role_tag,false);
	role2.roleInit(objects, cache, (role_tag == 1)?2:1,true);
	gameMap->addChild(role1.role, 3);
	gameMap->addChild(role2.role, 3);
	m_Roles[0] = &role1;
	m_Roles[1] = &role2;
	//initial face direction
	initFaceDirection(m_Roles, cache);
	opponent = 1;

	role1.hasUpReleased = true;
	role1.hasDownReleased = true;
	role1.hasLeftReleased = true;
	role1.hasRightReleased = true;
	role2.hasUpReleased = true;
	role2.hasDownReleased = true;
	role2.hasLeftReleased = true;
	role2.hasRightReleased = true;

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
			keys[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
			keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
			keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
			myPlayerInformation.isDownPressed = false;
			myPlayerInformation.isLeftPressed = false;
			myPlayerInformation.isRightPressed = false;
			role1.hasUpReleased = false;
			myPlayerInformation.isUpPressed = true;
			direction = kUp;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			keys[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
			keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
			keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
			myPlayerInformation.isUpPressed = false;
			myPlayerInformation.isLeftPressed = false;
			myPlayerInformation.isRightPressed = false;
			role1.hasDownReleased = false;
			myPlayerInformation.isDownPressed = true;
			direction = kDown;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			keys[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
			keys[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
			keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
			myPlayerInformation.isDownPressed = false;
			myPlayerInformation.isUpPressed = false;
			myPlayerInformation.isRightPressed = false;
			myPlayerInformation.isLeftPressed = true;
			role1.hasLeftReleased = false;
			direction = kLeft;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			keys[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
			keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
			keys[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
			myPlayerInformation.isDownPressed = false;
			myPlayerInformation.isLeftPressed = false;
			myPlayerInformation.isUpPressed = false;
			myPlayerInformation.isRightPressed = true;
			role1.hasRightReleased = false;
			direction = kRight;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			if (test_model == false) {
				myPlayerInformation.isSpacePressed = true;
				role1.dropBomb();
			}
			else if (test_model == true) {
				role2.dropBomb();
				}
			break;
			//role2
		case EventKeyboard::KeyCode::KEY_ENTER:
			if (test_model == true) {
				myPlayerInformation.isSpacePressed = true;
				role1.dropBomb();
			}
			break;
		case EventKeyboard::KeyCode::KEY_W:
			if (test_model == true) {
					keys[EventKeyboard::KeyCode::KEY_S] = false;
					keys[EventKeyboard::KeyCode::KEY_A] = false;
					keys[EventKeyboard::KeyCode::KEY_D] = false;
					role2.hasUpReleased = false;
					direction2 = kUp;
				}
			break;
		case EventKeyboard::KeyCode::KEY_S:
			if (test_model == true) {
					keys[EventKeyboard::KeyCode::KEY_W] = false;
					keys[EventKeyboard::KeyCode::KEY_A] = false;
					keys[EventKeyboard::KeyCode::KEY_D] = false;
					role2.hasDownReleased = false;
					direction2 = kDown;
				}
			break;
		case EventKeyboard::KeyCode::KEY_A:
			if (test_model == true) {
					keys[EventKeyboard::KeyCode::KEY_W] = false;
					keys[EventKeyboard::KeyCode::KEY_S] = false;
					keys[EventKeyboard::KeyCode::KEY_D] = false;
					role2.hasLeftReleased = false;
					direction2 = kLeft;
				}
			break;
		case EventKeyboard::KeyCode::KEY_D:
			if (test_model == true) {
					keys[EventKeyboard::KeyCode::KEY_S] = false;
					keys[EventKeyboard::KeyCode::KEY_A] = false;
					keys[EventKeyboard::KeyCode::KEY_W] = false;
					role2.hasRightReleased = false;
					direction2 = kRight;
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
			myPlayerInformation.isUpPressed = false;
			role1.hasUpReleased = true;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			myPlayerInformation.isDownPressed = false;
			role1.hasDownReleased = true;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			myPlayerInformation.isLeftPressed = false;
			role1.hasLeftReleased = true;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			myPlayerInformation.isRightPressed = false;
			role1.hasRightReleased = true;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			if (test_model == false) {
				myPlayerInformation.isSpacePressed = false;
			}
			break;
		case EventKeyboard::KeyCode::KEY_W:
			if (test_model == true) {
				role2.hasUpReleased = true;
			}
			break;
		case EventKeyboard::KeyCode::KEY_S:
			if (test_model == true) {
				role2.hasDownReleased = true;
			}
			break;
		case EventKeyboard::KeyCode::KEY_A:
			if (test_model == true) {
				role2.hasLeftReleased = true;
			}
			break;
		case EventKeyboard::KeyCode::KEY_D:
			if (test_model == true) {
				role2.hasRightReleased = true;
			}
			break;
		case EventKeyboard::KeyCode::KEY_ENTER:
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

	this->scheduleUpdate();
	this->schedule(schedule_selector(MapOfGame::moveUpdate), 0.05f);
	this->schedule(schedule_selector(MapOfGame::timer), 1.0f);

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

MapOfGame::~MapOfGame() {
	this->unscheduleAllSelectors();
}
//exchange information
void MapOfGame::update(float dt) {
	if (test_model == false) {
		message();
	}
	myPlayerInformation.role_x = role1.getPosition().x;
	myPlayerInformation.role_y = role1.getPosition().y;
	if (othermessage[2] == '1' || othermessage[3] == '1' || othermessage[4] == '1' || othermessage[5] == '1') {
		int x, y;
		x = (othermessage[7] - 48) * 100 + (othermessage[8] - 48) * 10 + othermessage[9] - 48;
		y = (othermessage[10] - 48) * 100 + (othermessage[11] - 48) * 10 + othermessage[12] - 48;
		role2.role->setPosition(ccp(x,y));
	}
	if (role1.hasUpReleased == true && role1.hasDownReleased == true && role1.hasLeftReleased == true && role1.hasRightReleased == true&&!role1.killedOrNot())
		direction = kStop;
	if (role1.killedOrNot())
		direction = kStart;
	if (test_model == true) {
		if (role2.hasUpReleased == true && role2.hasDownReleased == true && role2.hasLeftReleased == true && role2.hasRightReleased == true && !role2.killedOrNot())
			direction2 = kStop;
		if (role2.killedOrNot())
			direction2 = kStart;
	}
	else {
		if (othermessage[2] == '1')
			direction2 = kUp;
		else if (othermessage[3] == '1')
			direction2 = kDown;
		else if (othermessage[4] == '1')
			direction2 = kLeft;
		else if (othermessage[5] == '1')
			direction2 = kRight;
		else
			direction2 = kStop;
  		if (othermessage[6] == '1') {
			role2.dropBomb();
			/*int x = othermessage[13] - 48;
 			int y = othermessage[14] - 48;
			if (x >= 0 && x <= 14 && y >= 0 && y <= 12) {
				role2.dropBomb(x,12-y);
			}*/
		}
		if (isHost == false) {
			/*for (int i = 0; i < 195; i++) {
				if (othermessage[18 + i] != '\0') {
					int itemType = othermessage[18 + i] - 48;
					int tx = i % 15;
					int ty = i / 15;
					CCPoint tposition = ccp(tx, ty);
					if (itemInfo[i] != 'r')
						auto item = new Item(itemType, tposition, gameMap);
					itemInfo[i] = 'r';
				}
			}*/
			gameTime = (othermessage[15] - 48) * 100 + (othermessage[16] - 48) * 10 + othermessage[17] - 48;
		}
	}
	if(!role1.deletedOrNot())
		role1.keyPressedAnimation(direction);
	if(!role2.deletedOrNot())
		role2.keyPressedAnimation(direction2);
}
//count the gameTime
void MapOfGame::timer(float delta) {
	if (test_model == true || (test_model == false && isHost == true)) {
		seconds += delta;
		gameTime = seconds;
	}
	else if (test_model == false && isHost == false)
		seconds = gameTime;
	int temp = 180 - seconds;
	strstream ss;
	string s;
	ss << temp;
	ss >> s;
	if (seconds > 0 || temp >180 )
		this->removeChild(numberAtlas);
	numberAtlas = CCLabelAtlas::create("0123456789", "MapScene/number.png", 12, 10, '0');
	numberAtlas->setPosition(ccp(720, 548));
	numberAtlas->setString(s);
	this->addChild(numberAtlas);
	if(seconds >= 180 && seconds < 181)
		judgeResult(false);
}
//control the role's behavior
void MapOfGame::moveUpdate(float delta) {
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
		backToRoom();

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

void MapOfGame::backToRoom() {
	hasBackRun = true;
	auto director = Director::getInstance();
	auto scene = Hall::createScene();
	auto transition = TransitionCrossFade::create(0.5f, scene);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Prepare.mp3", true);
	if (test_model == false)
		closeServer = true;
	director->pushScene(transition);
}
void MapOfGame::BackTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto scene = Login::createScene();
		auto transition = TransitionCrossFade::create(0.5f, scene);
		director->pushScene(transition);
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
	switch (map_tag)
	{
	case 1:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Forest.mp3", true);
		break;
	case 2:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Village.mp3", true);
		break;
	case 3:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Factory.mp3", true);
		break;
	case 4:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Urban.mp3", true);
		break;
	case 5:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Mine.mp3", true);
		break;
	default:
		break;
	}
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
		for (int i = 1; i <= it->showBombRange(); i++)
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