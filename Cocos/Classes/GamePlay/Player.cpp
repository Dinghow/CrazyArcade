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

void Player::roleInit(CCTMXObjectGroup *objects,cocos2d::SpriteFrameCache* cache,int point) {
	switch (role_tag)
	{
	case 1:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("RoleSource/bazzi.plist");
		this->setProperties(6.5, 1, 1);
		break;
	case 2:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("RoleSource/cappi.plist");
		this->setProperties(6.0, 1, 1);
		break;
	default:
		cache->removeSpriteFrames();
		cache->addSpriteFramesWithFile("RoleSource/bazzi.plist");
		this->setProperties(6.5, 1, 1);
		break;
	}
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

Animation* Player::createDeadAnimation()
{
	CCSpriteFrameCache* deadFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	deadFrameCache->addSpriteFramesWithFile("res/Role/bazzi.plist", "res/Role/bazzi.png");
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= 8; i++)
	{
		auto* frame = deadFrameCache->getSpriteFrameByName(String::createWithFormat("role/wrapped_%d.png", i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	return animation;
}

void Player::setRoleDead()
{
	auto deadRoleAnimation = createDeadAnimation();
	deadRoleAnimation->setDelayPerUnit(0.5f);
	deadRoleAnimation->setLoops(1);
	auto deadRoleAnimate = Animate::create(deadRoleAnimation);
	role->runAction(deadRoleAnimate);
	this->schedule(schedule_selector(Player::deadUpdate), 0.1f);
}

void Player::deadUpdate(float dt)
{
	m_DeadTime += dt;
	if (m_DeadTime >= 2.0f && m_DeadTime <= 2.1f) {
		SimpleAudioEngine::getInstance()->playEffect("MusicSource/die.wav");
		shadow->setAnchorPoint(Vec2(-0.2,-0.2));
	}
	if (m_DeadTime >= 3.5f)
	{
		setDeleted();
		this->unschedule(schedule_selector(Player::deadUpdate));
	}

}
