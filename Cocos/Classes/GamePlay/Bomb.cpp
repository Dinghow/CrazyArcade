#include "bomb.h"
#include "Item.h"
#include <vector>
using namespace cocostudio::timeline;


CCPoint cBomb::getBombPosition()
{
	int tx = m_Role1->getPosition().x / static_cast<int>(m_Map->getTileSize().width);
	int ty = m_Role1->getPosition().y / static_cast<int>(m_Map->getTileSize().height);
	int x = (static_cast<float>(tx) + 0.5) * m_Map->getTileSize().width;
	int y = (static_cast<float>(ty) + 0.5) * m_Map->getTileSize().height;
	return ccp(x, y);
}

CCPoint cBomb::getGrid()
{
	int tx = m_Role1->getPosition().x / static_cast<int>(m_Map->getTileSize().width);
	int ty = (m_Map->getTileSize().height*m_Map->getMapSize().height- m_Role1->getPosition().y) / static_cast<int>(m_Map->getTileSize().height);
	return ccp(tx, ty);
}

Animation* cBomb::creatBombAnimation()
{
	CCSpriteFrameCache* bombFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	bombFrameCache->addSpriteFramesWithFile("res/Bomb/bomb.plist", "res/Bomb/bomb.png");
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= 3; i++)
	{
		auto* frame = bombFrameCache->getSpriteFrameByName(String::createWithFormat("bomb%d.png", i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	return animation;
}

//drop the bomb, idle time is 4.0s
void cBomb::dropBomb()
{
	if (m_Dropped)
		return;

	m_BombPosition = getBombPosition();
	m_TBombPosition = getGrid();
	m_Dropped = true;
	//获取对象数组
	TMXObjectGroup* objG = m_Map->getObjectGroup("objects");
	auto object = objG->getObject("object");

	//create Shadow
	CCSprite* shadow = CCSprite::create("Bomb/bomb4.png");
	shadow->setAnchorPoint(Vec2(0, 0));
	shadow->setPosition(ccp(0, 0));
	m_AllSprites.pushBack(shadow);

	//create the bomb sprite and run the animation
	auto bombAnimation = creatBombAnimation();
	auto layer = m_Map->layerNamed("architecture-real");
	CCSprite* bomb = CCSprite::create("Bomb/bomb1.png");
	m_AllSprites.pushBack(bomb);
	bomb->setPosition(m_BombPosition);
	bombAnimation->setLoops(3);
	bombAnimation->setDelayPerUnit(0.5f);
	m_Map->addChild(bomb,1);
	bomb->addChild(shadow, -1);

	auto bombAnimate = Animate::create(bombAnimation);
	bomb->runAction(bombAnimate);
 	this->schedule(schedule_selector(cBomb::idleUpdate),0.2f);
}

Animation* cBomb::creatExplodeAnimation(dire direction)
{
	auto explodeFrameCache = SpriteFrameCache::getInstance();
	explodeFrameCache->addSpriteFramesWithFile("Bomb/explosion.plist", "Bomb/explosion.png");
	Vector<SpriteFrame*> frameArray;

	for (int i = 0; i < 3; i++)
	{
		auto* frame = explodeFrameCache->getSpriteFrameByName(String::createWithFormat("explosion%d%d.png", direction + 1, i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.3f);
	animation->setLoops(1);
	return animation;
}

Animation* cBomb::creatCenterAnimation()
{
	auto explodeFrameCache = SpriteFrameCache::getInstance();
	explodeFrameCache->addSpriteFramesWithFile("Bomb/explosion.plist", "Bomb/explosion.png");
	Vector<SpriteFrame*> centerFrameArray;
	for (int i = 0; i < 3; i++)
	{
		auto* frame = explodeFrameCache->getSpriteFrameByName(String::createWithFormat("explosion0%d.png", i)->getCString());
		centerFrameArray.pushBack(frame);
	}
	Animation* centerAnimation = Animation::createWithSpriteFrames(centerFrameArray);
	centerAnimation->setLoops(1);
	centerAnimation->setDelayPerUnit(0.3);
	return centerAnimation;
}

void cBomb::explosion(dire direction)
{
	int iLen = 0;
	auto* layer = m_Map->layerNamed("architecture-real");
	auto tposition = m_TBombPosition;

	//get boundary the explosion could reach in specified direction
	for (int i = 1; i <= m_BombRange; i++)
	{
		tposition = ccpAdd(tposition, points[direction]);
		if (tposition.x > 14 || tposition.x < 0 || tposition.y < 0 || tposition.y>12)
			break;
		int gid = layer->getTileGIDAt(tposition);

		if (gid > 0)
		{
			Value prop = m_Map->getPropertiesForGID(gid);
			ValueMap propValueMap = prop.asValueMap();

			std::string destructible = propValueMap["destructible"].asString();

			if ("true" == destructible)
				iLen++;

			break;
		}
		else
			iLen++;
	}
<<<<<<< HEAD
=======
	m_Board[direction] = iLen;
>>>>>>> origin/hpc

	//create the explosion effect except the boundary
	for (int i = 1; i < iLen; i++)
	{
		char str[100];
		sprintf(str, "Bomb/explosion%d5.png", direction + 1);
		CCSprite* sprite = Sprite::create(str);
		m_AllSprites.pushBack(sprite);
		auto delta = ccp(i*m_Map->getTileSize().width*points[direction].x,
			-i*m_Map->getTileSize().height*points[direction].y);
		sprite->setPosition(ccpAdd(m_BombPosition, delta));
		m_Map->addChild(sprite,1);
	}

	//create the explosion effect at the boundary
	if (iLen > 0)
	{
		Animate* animate = Animate::create(creatExplodeAnimation(direction));
		char str[100];
		sprintf(str, "Bomb/explosion%d0.png", direction + 1);
		CCSprite* sprite = Sprite::create(str);
		sprite->setPosition(ccpAdd(m_BombPosition, ccp(iLen*m_Map->getTileSize().width*points[direction].x,
			-iLen*m_Map->getTileSize().height*points[direction].y)));
		m_AllSprites.pushBack(sprite);
		m_Map->addChild(sprite,1);
		sprite->runAction(animate);
	}

	removeTile(direction);
}

//0.6s
void cBomb::explode()
{
	auto* layer = m_Map->layerNamed("architecture-real");
	//center animation
	CCSprite* center = CCSprite::create("Bomb/explosion00.png");
	m_AllSprites.pushBack(center);
	center->setPosition(m_BombPosition);
	m_Map->addChild(center,1);
	auto centerAnimation = creatCenterAnimation();
	auto* centerAnimate = Animate::create(centerAnimation);
	center->runAction(centerAnimate);

	//The four directions animations
	explosion(UP);
	explosion(RIGHT);
	explosion(DOWN);
	explosion(LEFT);
}


void cBomb::idleUpdate(float dt)
{
	m_CurrentTime += dt;
	if (m_CurrentTime >= 4.0f)
	{
		this->unschedule(schedule_selector(cBomb::idleUpdate));
		for (auto* it : m_AllSprites)
			m_Map->removeChild(it);
		m_AllSprites.clear();
		m_Exploded = true;
		explode();
		m_CurrentTime = 0;
		this->schedule(schedule_selector(cBomb::explodeUpdate), 0.1f);
	}
}

void cBomb::explodeUpdate(float dt)
{
	m_CurrentTime += dt;
	if (m_CurrentTime >= 0.6f)
	{
		for (auto* it : m_AllSprites)
			m_Map->removeChild(it);
		m_AllSprites.clear();
		m_Dropped = false;
		m_Exploded = false;

		unschedule(schedule_selector(cBomb::explodeUpdate));
	}
}

void cBomb::removeTile(dire direction)
{
	auto* layer1 = m_Map->layerNamed("architecture-real");
	auto* layer2 = m_Map->layerNamed("architecture-float");
	auto tposition = m_TBombPosition;

	for (int i = 1; i <= m_BombRange; i++)
	{
		tposition = ccpAdd(tposition, points[direction]);
		if (tposition.x > 14 || tposition.x < 0 || tposition.y < 0 || tposition.y>12)
			break;

		int gid1 = layer1->getTileGIDAt(tposition);

		if (gid1 > 0)
		{
			Value prop1 = m_Map->getPropertiesForGID(gid1);
			ValueMap propValueMap1 = prop1.asValueMap();

			std::string destructible = propValueMap1["destructible"].asString();

			if ("true" == destructible)
			{
				layer1->removeTileAt(tposition);
				if (tposition.y > 0)
				{
					int gid2 = layer2->getTileGIDAt(ccpAdd(tposition, ccp(0, -1)));
					if (gid2 > 0)
					{
						layer2->removeTileAt(ccpAdd(tposition, ccp(0, -1)));

						//Drop items
						randomItem(tposition, m_Map);
						break;
					}
				}
			}
			else
				break;
		}
	}
}
