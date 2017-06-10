#include "Item.h"
#include <ctime>

int isItem[15][13] = { 0 };
Item* items[15][13] = { nullptr };

Item::Item(const std::string &itemName, const cocos2d::CCPoint &TPos, cocos2d::CCTMXTiledMap* m_Map) :
	tilePos(TPos), item(cocos2d::CCSprite::create(itemName)), Map(m_Map)
{
	cocos2d::Node::onEnter();

	item->setAnchorPoint(cocos2d::Vec2(0, 0));
	auto position = getItemPosition();
	item->setPosition(position);
	item->setVisible(true);
	Map->addChild(item, 2);
}

void Item::remove()
{
	//item->setVisible(false);
	Map->removeChild(item);
}

cocos2d::CCPoint Item::getItemPosition()
{
	float x = static_cast<float>(tilePos.x) * Map->getTileSize().width;
	float y = (Map->getMapSize().height - 1 - static_cast<float>(tilePos.y)) * Map->getTileSize().height;
	return cocos2d::Vec2(x, y);
}

int randNum()
{
	srand(time(nullptr));
	return rand();
}

int randomItem(const cocos2d::CCPoint &bombPos, const int &bombRange, cocos2d::CCTMXTiledMap* Map)
{
	int posNum = (randNum() % (2 * bombRange)) - bombRange;
	int itemNum = randNum() % 897;

	int itemNo = itemNum % 7;
	if ((itemNum > 897 * (1 - PROBABILITY)) && itemNo)
	{
		cocos2d::CCPoint itemPos = bombPos;
		if (itemNum % 2)
		{
			itemPos.x += posNum;
			if (itemPos.x < 0)
				itemPos.x = 0;
			else if (itemPos.x > 14)
				itemPos.x = 14;
		}
		else
		{
			itemPos.y += posNum;
			if (itemPos.y < 0)
				itemPos.y = 0;
			else if (itemPos.y > 12)
				itemPos.y = 12;
		}

		if (isItem[(int)itemPos.x][(int)itemPos.y])
			return 0;

		char name[16] = "\0";
		sprintf(name, "Item/item%d.png", itemNo);
		auto item = new Item(name, itemPos, Map);

		items[(int)itemPos.x][(int)itemPos.y] = item;
		isItem[(int)itemPos.x][(int)itemPos.y] = itemNo;

		//CCLOG("itemPos:%f %f", itemPos.x, itemPos.y);
		return 0;
	}
	return 0;
}