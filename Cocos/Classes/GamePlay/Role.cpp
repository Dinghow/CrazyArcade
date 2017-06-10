#include "Role.h"
using namespace cocostudio::timeline;

extern int isItem[15][13];
extern Item* items[15][13];

Role::Role() {
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

void Role::setProperties(int speed, int bombRange, int bombQuantity) {
	this->bombQuantity = bombQuantity;
	this->bombRange = bombRange;
	this->speed = speed;
	for (auto it : m_Bombs)
	{
		it->setBombRange(bombRange);
	}
}

void Role::loadPositon() {
	position = role->getPosition();
}

void Role::pickUpItem(const cocos2d::CCPoint &tilePos)
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
		(items[(int)tilePos.x][(int)tilePos.y])->remove();
		delete (items[(int)tilePos.x][(int)tilePos.y]);
		items[(int)tilePos.x][(int)tilePos.y] = nullptr;

	}
}

/**********************************************/
void Role::dropBomb()
{
	for (auto it : m_Bombs)
	{
		if (!it->droppedOrNot())
		{
			it->dropBomb();
			break;
		}
	}
}

void Role::addBomb()
{
	cBomb* bomb = new cBomb(bombRange);
	m_Bombs.push_back(bomb);
	bomb->getMap(m_Bombs[0]->returnMap());
	bomb->getRole(m_Bombs[0]->returnRole());
}

void Role::addBombRange()
{
	bombRange++;
	for (auto it : m_Bombs)
		it->addBombRange();
}

Animation* Role::createDeadAnimation()
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

void Role::setRoleDead()
{
	auto deadRoleAnimation = createDeadAnimation();
	deadRoleAnimation->setDelayPerUnit(0.5f);
	deadRoleAnimation->setLoops(1);
	auto deadRoleAnimate = Animate::create(deadRoleAnimation);
	role->runAction(deadRoleAnimate);
	this->schedule(schedule_selector(Role::deadUpdate), 0.1f);
}

void Role::deadUpdate(float dt)
{
	m_DeadTime += dt;
	if (m_DeadTime >= 3.5f)
	{
		setDeleted();
		this->unschedule(schedule_selector(Role::deadUpdate));
	}

}
