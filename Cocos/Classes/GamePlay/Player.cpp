#include "Player.h"
#include "CoordTransfer.h"
using namespace cocostudio::timeline;

static std::string animationByDirection[2][8] = {
	{ "owl_1.png" , "owl_2.png" , "owl_3.png", "owl_4.png", "owl_5.png", "owl_6.png", "owl_7.png", "owl_8.png" },
	{ "SlowTurtle_1.png" , "SlowTurtle_2.png" , "SlowTurtle_3.png", "SlowTurtle_4.png", "SlowTurtle_5.png", "SlowTurtle_6.png", "SlowTurtle_7.png", "SlowTurtle_8.png" }
};

static std::string faceDirect[2][3][4] = {
	{ { "bazzi_stop_up.png" , "bazzi_stop_down.png" , "bazzi_stop_left.png", "bazzi_stop_right.png" },
	{ "bazzi_owl_up.png" , "bazzi_owl_down.png" ,"bazzi_owl_left.png", "bazzi_owl_right.png" },
	{ "bazzi_SlowTurtle_up.png" , "bazzi_SlowTurtle_down.png" ,"bazzi_SlowTurtle_left.png", "bazzi_SlowTurtle_right.png" } },
	{ { "cappi_stop_up.png" , "cappi_stop_down.png" , "cappi_stop_left.png", "cappi_stop_right.png" },
	{ "cappi_owl_up.png" , "cappi_owl_down.png" ,"cappi_owl_left.png", "cappi_owl_right.png" },
	{ "cappi_SlowTurtle_up.png" , "cappi_SlowTurtle_down.png" ,"cappi_SlowTurtle_left.png", "cappi_SlowTurtle_right.png" } }
};


extern int isItem[15][13];
extern Item* items[15][13];

Player::Player() {
	onRide = 0;
	roleSelection = 1;
	bombQuantity = 1;
	bombRange = 1;
	speed = 6.5;

	m_CanNotBeKilledTime = 0;
	m_Killed = false;
	m_Deleted = false;
	m_Dying = false;
	m_CanNotBeKilled = false;
	cocos2d::Layer::onEnter();
	for (int i = 0; i < bombQuantity; i++)
	{
		cBomb* bomb = new cBomb(bombRange);
		m_Bombs.push_back(bomb);
	}
}

void Player::roleInit(CCTMXObjectGroup *objects,cocos2d::SpriteFrameCache* cache,int roleSelect,int isOpp) {
	isOpponent = isOpp;
	roleSelection = roleSelect;
	if (!isOpp)
		isMeAlive = true;
	nowDirection = kStart;
	switch (roleSelect)
	{
	case 1:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("Role/bazzi.plist","Role/bazzi.png");
		this->setProperties(6.5, 2, 1, 15, 4);
		break;
	case 2:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("Role/cappi.plist","Role/cappi.png");
		this->setProperties(6.0, 2, 1, 15, 4);
		break;
	default:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("Role/bazzi.plist","Role/bazzi.png");
		this->setProperties(6.5, 2, 1, 15, 4);
		break;
	}
	//load dead animations
	for (int i = 1; i <= 8; i++)
	{
		auto* frame = cache->getSpriteFrameByName(String::createWithFormat("wrapped_%d.png", i)->getCString());
		if (i <= 4) {
			frameArray1.pushBack(frame);
		}
		else if(i>=5)
			frameArray2.pushBack(frame);
	}
	deadAnimations[0] = new CCAnimation();
	deadAnimations[0]->initWithSpriteFrames(frameArray1, 0.3f);
	deadAnimations[1] = new CCAnimation();
	deadAnimations[1]->initWithSpriteFrames(frameArray2, 0.3f);
	deadAnimations[0]->setLoops(5);
	deadAnimations[1]->setLoops(1);

	//set first spawn point
	cocos2d::ValueMap spawnPoint;
	switch (roleSelect)
	{
	case 1:
		spawnPoint = objects->objectNamed("spawnpoint1");
		break;
	case 2:
		spawnPoint = objects->objectNamed("spawnpoint2");
		break;
	case 3:
		spawnPoint = objects->objectNamed("spawnpoint3");
		break;
	case 4:
		spawnPoint = objects->objectNamed("spawnpoint4");
		break;
	default:
		break;
	}
	int startX = spawnPoint.at("x").asInt();
	int startY = spawnPoint.at("y").asInt();
	startPosition = tilecoordForPosition(CCPoint(startX, startY));

	//create the role and set the first frame as the static condition
	role = Sprite::createWithSpriteFrameName("stop_down.png");
	role->setAnchorPoint(Vec2(0.5, 0.5));
	role->setPosition(ccp(startX + 20, startY + 28));
	this->loadPositon();    

	//add shadow for the role
	shadow = Sprite::create("Role/shadow.png");
	shadow->setAnchorPoint(Vec2(0, 0));
	shadow->setPosition(ccp(0, 0));
	role->addChild(shadow);
	shadow->setLocalZOrder(-1);
	//create the animation of four direction
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < kTotal; ++j)
			walkAnimations[i][j] = creatAnimationByDirecton(i, (RoleDirection)j, cache);
}

void Player::setProperties(float speed, int bombRange, int bombQuantity, int speedLimit, int bombQuantityLimit) {
	this->bombQuantity = bombQuantity;
	this->bombRange = bombRange;
	this->speed = speed;
	this->speedLimit = speedLimit;
	this->bombQuantity = bombQuantityLimit;
	this->preSpeed = this->speed;
	for (auto it : m_Bombs)
	{
		it->setBombRange(bombRange);
	}

}

void Player::loadPositon() {
	position = role->getPosition();
}

void Player::pickUpItem(const cocos2d::CCPoint &tilePos)
{
	if (isItem[(int)tilePos.x][(int)tilePos.y])
	{
		switch (isItem[(int)tilePos.x][(int)tilePos.y])
		{
		case 1:
			money += 100;
			break;
		case 2:
			money += 10;
			break;
		case 3:
			++money;
			break;
		case 4:
			addBombRange();
			break;
		case 5:
			addBomb();
			break;
		case 6:
			addSpeed();
			break;
		case 7:
			for (int i = 0; i < 4; ++i)
				addBombRange();
			break;
		case 8:
			roleOnRide(1);
			break;
		case 9:
			roleOnRide(2);
			break;
		}

		//remove items from maps
		isItem[(int)tilePos.x][(int)tilePos.y] = 0;
		SimpleAudioEngine::getInstance()->playEffect("MusicSource/get.wav");
		(items[(int)tilePos.x][(int)tilePos.y])->remove();
		delete (items[(int)tilePos.x][(int)tilePos.y]);
		items[(int)tilePos.x][(int)tilePos.y] = nullptr;

	}
}

void Player::roleOnRide(const int &No)
{
	onRide = No;
	role->setSpriteFrame(faceFrames[onRide][1]);
	if (No == 1)
	{
		speed += 3;
		if (speed > speedLimit)
			speed = speedLimit;
		cocos2d::JumpBy* jumpby = cocos2d::JumpBy::create(1.5, cocos2d::Vec2(0, 0), 3, 1);
		cocos2d::RepeatForever *jumpForever = cocos2d::RepeatForever::create(jumpby);
		jumpForever->setTag(1);
		role->runAction(jumpForever);
	}
	else if (No == 2)
		speed -= 3;
	if (speed <= 0)
		speed = 1;

	role->setAnchorPoint(Vec2(0.5, 0.25));
}

/**********************************************/
void Player::dropBomb()
{
	if (!killedOrNot())
	{
		bool empty = true;
		auto roleTileCoord = tilecoordForPosition(role->getPosition());
		for (auto it : m_Bombs)
		{
			if (it->droppedOrNot())
				if (roleTileCoord == tilecoordForPosition(it->bombOpenglCoord()))
				{
					empty = false;
					break;
				}
		}
		if (empty) {
			for (auto it : m_Bombs)
			{
				if (!it->droppedOrNot())
				{
					it->dropBomb();
					myPlayerInformation.bomb_x = roleTileCoord.x;
					myPlayerInformation.bomb_y = roleTileCoord.y;
					SimpleAudioEngine::getInstance()->playEffect("MusicSource/appear.wav");
					break;
				}
			}
		}
	}
}

void Player::dropBomb(int x,int y)
{
	if (!killedOrNot())
	{
		for (int i=0;i<m_Bombs.size();i++)
		{
 			if (!m_Bombs[i]->droppedOrNot())
			{
				m_Bombs[i]->dropBomb(x, y);
				bombNumber = i+1;
				SimpleAudioEngine::getInstance()->playEffect("MusicSource/appear.wav");
				break;
			}
		}
	}
}

void Player::addBomb()
{
	cBomb* bomb = new cBomb(bombRange);
	m_Bombs.push_back(bomb);
	bomb->getMap(m_Bombs[0]->returnMap());
	bomb->getRole(m_Bombs[0]->returnRole());
}

void Player::addBombRange()
{
	bombRange++;
	for (auto it : m_Bombs)
		it->addBombRange();
}

void Player::roleDying()
{
	auto deadAnimate = CCAnimate::create(deadAnimations[0]);
	role->setLocalZOrder(5);
	role->runAction(deadAnimate);
}

void Player::roleDelete()
{
	auto deleteAnimate = CCAnimate::create(deadAnimations[1]);
	role->setLocalZOrder(2);
	role->runAction(deleteAnimate);
	if (this->isOpponent == true) {
		opponent--;
	}
	else if (this->isOpponent == false)
		isMeAlive = false;
}

void Player::setRoleDead()
{
	roleDying();
	this->schedule(schedule_selector(Player::deadUpdate), 0.1f);
}

void Player::deadUpdate(float dt)
{
	m_DeadTime += dt;
	if (m_DeadTime >= 5.7f && m_DeadTime <= 5.8f) {
		role->stopAllActions();
		roleDelete();
		SimpleAudioEngine::getInstance()->playEffect("MusicSource/die.wav");
		shadow->setAnchorPoint(Vec2(-0.2,-0.2));
	}

	if (m_DeadTime >= 6.6f)
	{
		setDeleted();
		this->unschedule(schedule_selector(Player::deadUpdate));
	}

}

//create animation frames
CCAnimation* Player::creatAnimationByDirecton(int ride, RoleDirection direction, cocos2d::SpriteFrameCache* cache) {
	if (ride)
	{
		Vector<SpriteFrame*> frames(2);
		switch (direction)
		{
		case kUp:case kDown:case kLeft:case kRight:
			for (int i = 2 * direction; i < 2 * (direction + 1); ++i)
			{
				auto frame = cache->getSpriteFrameByName(animationByDirection[ride - 1][i]);
				frames.pushBack(frame);
			}
			break;
		default:
			break;
		}
		CCAnimation* animation = new CCAnimation();
		animation->initWithSpriteFrames(frames, 0.2f);

		return animation;
	}
	else
	{
		Vector<SpriteFrame*> frames(5);
		cocos2d::SpriteFrame* frame1, *frame2, *frame3, *frame4, *frame5;
		switch (direction)
		{
		case kUp:
			frame1 = cache->getSpriteFrameByName("stop_up.png");
			frame2 = cache->getSpriteFrameByName("move_up_1.png");
			frame3 = cache->getSpriteFrameByName("move_up_2.png");
			frame4 = cache->getSpriteFrameByName("move_up_3.png");
			frame5 = cache->getSpriteFrameByName("move_up_4.png");
			frames.pushBack(frame1);
			frames.pushBack(frame2);
			frames.pushBack(frame3);
			frames.pushBack(frame4);
			frames.pushBack(frame5);
			break;

		case kDown:
			frame1 = cache->getSpriteFrameByName("stop_down.png");
			frame2 = cache->getSpriteFrameByName("move_down_1.png");
			frame3 = cache->getSpriteFrameByName("move_down_2.png");
			frame4 = cache->getSpriteFrameByName("move_down_3.png");
			frame5 = cache->getSpriteFrameByName("move_down_4.png");
			frames.pushBack(frame1);
			frames.pushBack(frame2);
			frames.pushBack(frame3);
			frames.pushBack(frame4);
			frames.pushBack(frame5);
			break;

		case kLeft:
			frame1 = cache->getSpriteFrameByName("stop_left.png");
			frame2 = cache->getSpriteFrameByName("move_left_1.png");
			frame3 = cache->getSpriteFrameByName("move_left_2.png");
			frame4 = cache->getSpriteFrameByName("move_left_3.png");
			frame5 = cache->getSpriteFrameByName("move_left_4.png");
			frames.pushBack(frame1);
			frames.pushBack(frame2);
			frames.pushBack(frame3);
			frames.pushBack(frame4);
			frames.pushBack(frame5);
			break;

		case kRight:
			frame1 = cache->getSpriteFrameByName("stop_right.png");
			frame2 = cache->getSpriteFrameByName("move_right_1.png");
			frame3 = cache->getSpriteFrameByName("move_right_2.png");
			frame4 = cache->getSpriteFrameByName("move_right_3.png");
			frame5 = cache->getSpriteFrameByName("move_right_4.png");
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
}

//the event during key pressed
void Player::keyPressedAnimation(RoleDirection direction) {
	if (this->nowDirection == direction)
		return;
	else if (direction == kStart)
		return;
	else if (direction == kStop) {
		this->setFaceDirection(this->nowDirection);
	}
	else{
		if(this->nowDirection != kStart)
			role->stopAction(animations[this->nowDirection]);
		//you can set move speed here
		animations[direction] = RepeatForever::create(CCAnimate::create(walkAnimations[onRide][direction]));
		role->runAction(animations[direction]);
		this->nowDirection = direction;
	}
}

void Player::keyPressedMovement(EventKeyboard::KeyCode keyCode) {
	CCPoint moveByPosition;
	CCPoint tempPosition;
	RoleDirection tag;
	//you can set move speed here
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		moveByPosition = ccp(0, this->getSpeed());
		tag = kUp;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		moveByPosition = ccp(0, -this->getSpeed());
		tag = kDown;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		moveByPosition = ccp(-this->getSpeed(), 0);
		tag = kLeft;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveByPosition = ccp(this->getSpeed(), 0);
		tag = kRight;
		break;
	default:
		moveByPosition = ccp(0, 0);
		break;
	}
	//collision check
	//CCPoint targetPosition = ccpAdd(this->getPosition(), moveByPosition);
	CCPoint targetPosition = ccp(this->position.x + moveByPosition.x, this->position.y + moveByPosition.y);

	while (checkCollision(this->getPosition(), targetPosition, tag) == kWall){
		switch (tag) {
		case kUp:
			tempPosition = ccp(0, -0.5);
			targetPosition = ccpAdd(targetPosition, tempPosition);
			break;
		case kDown:
			tempPosition = ccp(0, 0.5);
			targetPosition = ccpAdd(targetPosition, tempPosition);
			break;
		case kLeft:
			tempPosition = ccp(0.5,0);
			targetPosition = ccpAdd(targetPosition, tempPosition);
			break;
		case kRight:
			tempPosition = ccp(-0.5, 0);
			targetPosition = ccpAdd(targetPosition, tempPosition);
			break;
		default:
			tempPosition = ccp(0, 0);
			break;
		}
	}

	auto move = CCMoveTo::create(0.01f, targetPosition);
	role->runAction(move);
}

//set face direciton
void Player::setFaceDirection(RoleDirection direction) {
	switch (direction) {
	case kUp:
		this->role->setSpriteFrame(faceFrames[onRide][kUp]);
		break;
	case kDown:
		this->role->setSpriteFrame(faceFrames[onRide][kDown]);
		break;
	case kLeft:
		this->role->setSpriteFrame(faceFrames[onRide][kLeft]);
		break;
	case kRight:
		this->role->setSpriteFrame(faceFrames[onRide][kRight]);
		break;
	default:
		break;
	}
}


//the call back function of finished walk
void Player::onWalkDone(RoleDirection direction) {
	this->setFaceDirection(direction);
}

void Player::getKilled()
{
	if (m_CanNotBeKilled)
		return;

	if (onRide)
	{
		if (onRide == 1)
			role->stopActionByTag(1);
		onRide = 0;
		speed = preSpeed;
		m_CanNotBeKilled = true;
		m_CanNotBeKilledTime = 0.0f;

		auto blink = Blink::create(1, 10);
		role->runAction(blink);
		role->setAnchorPoint(Vec2(0.5, 0.5));
		this->schedule(schedule_selector(Player::canNotBeKilledUpdate), 0.1f);
	}
	else
	{
		m_Killed = true;
		speed = 1.5;
	}
}

void Player::canNotBeKilledUpdate(float dt)
{
	m_CanNotBeKilledTime += dt;
	if (m_CanNotBeKilledTime >= 1.0)
	{
		role->setSpriteFrame(faceFrames[0][1]);
		m_CanNotBeKilled = false;
		this->unschedule(schedule_selector(Player::canNotBeKilledUpdate));
	}
}

void initFaceDirection(Player* Roles[2], cocos2d::SpriteFrameCache* cache)
{
	cache->addSpriteFramesWithFile("Role/bazziDirect.plist", "Role/bazziDirect.png");
	cache->addSpriteFramesWithFile("Role/cappiDirect.plist", "Role/cappiDirect.png");

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 4; ++k)
			{
				if (Roles[i]->roleSelection == 1)
					Roles[i]->faceFrames[j][k] = SpriteFrameCache::getInstance()->getSpriteFrameByName(faceDirect[0][j][k]);
				else if (Roles[i]->roleSelection == 2)
					Roles[i]->faceFrames[j][k] = SpriteFrameCache::getInstance()->getSpriteFrameByName(faceDirect[1][j][k]);
			}

}