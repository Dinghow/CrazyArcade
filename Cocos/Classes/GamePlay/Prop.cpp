#include "Prop.h"

CCSprite* cProp::createPropSprite(buff kind)
{
	switch (kind)
	{
	case QUANTITY:
		CCSprite* prop = CCSprite::create("Prop/quantity.png");
		return prop;
	case RANGE:
		CCSprite* prop = CCSprite::create("Prop/range.png");
		return prop;
	case SPEED_ADD:
		CCSprite* prop = CCSprite::create("Prop/speedAdd.png");
		return prop;
	default:
		break;
	}
}

void cProp::createProp()
{
	m_Sprite = createPropSprite(m_Kind);
	auto posotion = ccp((m_tPosition.x + 0.5)*m_Map->getTileSize().width,
		(m_Map->getMapSize().height - m_tPosition.y + 0.5)*m_Map->getTileSize().height);
	m_Map->addChild(m_Sprite, 1);
}

void cProp::removeProp()
{
	m_Map->removeChild(m_Sprite);
}