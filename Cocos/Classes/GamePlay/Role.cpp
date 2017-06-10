#include "Role.h"
using namespace cocostudio::timeline;
Role::Role() {
	bombQuantity = 5;
	bombRange = 3;
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
}

void Role::loadPositon() {
	position = role->getPosition();
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
