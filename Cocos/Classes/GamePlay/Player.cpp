#include "Player.h"
#include "CoordTransfer.h"
using namespace cocostudio::timeline;

extern int isItem[15][13];
extern Item* items[15][13];

Player::Player() {
	bombQuantity = 1;
	bombRange = 1;
	speed = 6.5;
	m_Killed = false;
	m_Deleted = false;
	m_Dying = false;
	cocos2d::Layer::onEnter();
	for (int i = 0; i < bombQuantity; i++)
	{
		cBomb* bomb = new cBomb(bombRange);
		m_Bombs.push_back(bomb);
	}
}

void Player::roleInit(CCTMXObjectGroup *objects,cocos2d::SpriteFrameCache* cache,int point,int roleSelect,int isOpp) {
	isOpponent = isOpp;
	if (!isOpp)
		isMeAlive = true;
	switch (roleSelect)
	{
	case 1:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("Role/bazzi.plist","Role/bazzi.png");
		this->setProperties(6.5, 2, 1);
		break;
	case 2:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("Role/cappi.plist","Role/cappi.png");
		this->setProperties(6.0, 2, 1);
		break;
	default:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("Role/bazzi.plist","Role/bazzi.png");
		this->setProperties(6.5, 2, 1);
		break;
	}
	//load dead animations
	for (int i = 1; i <= 8; i++)
	{
		auto* frame = cache->getSpriteFrameByName(String::createWithFormat("role/wrapped_%d.png", i)->getCString());
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
	//load init frame
	faceFrames[0] = SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_up.png");
	faceFrames[1] = SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_down.png");
	faceFrames[2] = SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_left.png");
	faceFrames[3] = SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_right.png");
	//set first spawn point
	cocos2d::ValueMap spawnPoint;
	switch (point)
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
	role = Sprite::createWithSpriteFrameName("role/stop_down.png");
	role->setAnchorPoint(Vec2(0.5, 0.5));
	role->setPosition(ccp(startX + 20, startY + 28));

	//add shadow for the role
	shadow = Sprite::create("Role/shadow.png");
	shadow->setAnchorPoint(Vec2(0, 0));
	shadow->setPosition(ccp(0, 0));
	role->addChild(shadow);
	shadow->setLocalZOrder(-1);
	//create the animation of four direction
	for (int i = 0; i < kTotal; i++) {
		walkAnimations[i] = creatAnimationByDirecton((RoleDirection)i, cache);
	}
}

void Player::setProperties(int speed, int bombRange, int bombQuantity) {
	this->bombQuantity = bombQuantity;
	this->bombRange = bombRange;
	this->speed = speed;
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
		}

		//remove items from maps
		isItem[(int)tilePos.x][(int)tilePos.y] = 0;
		SimpleAudioEngine::getInstance()->playEffect("MusicSource/get.wav");
		(items[(int)tilePos.x][(int)tilePos.y])->remove();
		delete (items[(int)tilePos.x][(int)tilePos.y]);
		items[(int)tilePos.x][(int)tilePos.y] = nullptr;

	}
}

/**********************************************/
void Player::dropBomb()
{
	for (auto it : m_Bombs)
	{
		if (!it->droppedOrNot())
		{
			it->dropBomb();
			SimpleAudioEngine::getInstance()->playEffect("MusicSource/appear.wav");
			break;
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
CCAnimation* Player::creatAnimationByDirecton(RoleDirection direction, cocos2d::SpriteFrameCache* cache) {
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

//the event during key pressed
void Player::keyPressedAnimation(EventKeyboard::KeyCode keyCode) {
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
	role->runAction(animations[tag]);
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
	CCPoint targetPosition = ccpAdd(this->getPosition(), moveByPosition);

	while (checkCollision(this->getPosition(), targetPosition, tag) == kWall) {
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
		this->role->setSpriteFrame(faceFrames[kUp]);
		break;
	case kDown:
		this->role->setSpriteFrame(faceFrames[kDown]);
		break;
	case kLeft:
		this->role->setSpriteFrame(faceFrames[kLeft]);
		break;
	case kRight:
		this->role->setSpriteFrame(faceFrames[kRight]);
		break;
	default:
		break;
	}
}


//the call back function of finished walk
void Player::onWalkDone(RoleDirection direction) {
	this->setFaceDirection(direction);
}