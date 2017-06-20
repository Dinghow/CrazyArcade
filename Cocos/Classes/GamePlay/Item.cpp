#include "Item.h"
#include "Data.h"

int isItem[15][13] = { 0 };
Item* items[15][13] = { nullptr };
int fixedItems[3][15][13] = {
	{
		{ 0,2,2,4,2,5,5,0,3,0,7,7,0 },
		{ 1,9,5,4,5,1,3,1,6,2,4,9,5 },
		{ 1,7,8,6,1,9,4,4,4,5,9,2,6 },
		{ 3,5,8,4,8,2,0,5,9,0,0,7,5 },
		{ 7,8,3,6,3,1,4,1,0,7,5,2,5 },
		{ 7,3,4,4,2,1,4,4,0,9,6,0,2 },
		{ 8,1,0,8,1,1,2,1,7,8,5,7,9 },
		{ 2,9,7,9,7,5,8,2,0,6,1,9,4 },
		{ 4,5,6,5,0,2,2,9,1,0,0,6,2 },
		{ 0,3,3,1,1,0,8,4,9,5,9,4,6 },
		{ 1,4,8,7,0,7,7,4,6,4,3,6,3 },
		{ 4,0,6,5,1,7,1,0,4,2,8,1,7 },
		{ 2,5,2,1,4,7,5,4,4,8,9,8,2 },
		{ 4,2,3,9,0,3,8,6,6,5,2,3,0 },
		{ 4,3,4,9,5,8,8,7,9,0,5,4,9 }
	},

	{ 
		{ 5,5,8,7,5,1,6,5,0,7,5,4,0 },
		{ 0,7,1,9,2,2,5,9,2,6,2,6,3 },
		{ 7,1,3,4,9,2,1,4,4,2,9,0,5 },
		{ 4,8,1,3,8,8,7,4,6,4,9,5,5 },
		{ 6,1,7,2,8,4,6,4,8,9,8,8,7 },
		{ 6,2,6,0,2,9,7,5,3,8,0,3,8 },
		{ 6,8,5,2,9,4,0,7,6,7,7,1,4 },
		{ 1,5,6,7,3,8,9,4,0,2,5,1,6 },
		{ 0,2,1,8,5,0,7,8,1,1,0,8,3 },
		{ 7,2,6,3,0,1,7,8,4,1,1,2,5 },
		{ 9,9,3,9,4,5,0,0,4,4,9,3,2 },
		{ 2,8,8,2,0,9,0,2,2,0,1,7,0 },
		{ 3,1,3,9,0,9,6,6,1,3,2,6,2 },
		{ 4,2,1,5,5,3,5,0,6,7,2,5,7 },
		{ 2,7,0,8,0,0,5,8,3,6,0,2,4 },
	},
	{ 
		{ 5,8,4,8,3,5,3,1,8,7,5,2,6 },
		{ 7,5,8,1,5,6,2,1,9,9,2,5,7 },
		{ 2,2,0,3,3,3,2,6,4,4,4,7,7 },
		{ 5,2,8,9,2,0,4,3,8,8,9,6,2 },
		{ 5,8,5,0,4,5,4,1,2,8,8,5,2 },
		{ 4,1,2,5,7,6,0,3,7,8,7,9,4 },
		{ 8,6,2,6,4,9,2,8,0,2,4,3,3 },
		{ 7,9,8,1,8,5,8,8,4,2,8,0,7 },
		{ 2,8,8,2,6,8,7,0,3,8,6,6,3 },
		{ 0,6,1,7,1,9,0,2,5,4,3,4,9 },
		{ 2,3,2,8,6,3,7,3,9,7,3,8,1 },
		{ 8,6,5,4,3,8,6,4,3,8,3,7,5 },
		{ 5,0,8,7,2,5,5,8,1,8,5,6,2 },
		{ 7,4,3,4,7,4,5,7,5,0,3,4,7 },
		{ 4,6,8,6,0,5,1,0,0,5,8,0,5 }
	}
};

Item::Item(int &itemno, const cocos2d::CCPoint &TPos, cocos2d::CCTMXTiledMap* m_Map) :tilePos(TPos), Map(m_Map),itemNo(itemno)
{
	cocos2d::Node::onEnter();
	
	//create item
	auto position = getItemPosition();
	auto itemName = cocos2d::String::createWithFormat("Item/item%d__.png", itemNo);
	item = cocos2d::Sprite::create(itemName->getCString());
	item->setAnchorPoint(cocos2d::Vec2(0, 0));
	item->setPosition(position);
	item->setVisible(true);
	Map->addChild(item, 2.5);
	
	//transport the item information
	if(isHost)
		itemInfo[static_cast<int>(TPos.y * 15 + TPos.x)] = itemNo + 48;

	//make items jump up and down
	cocos2d::JumpBy* jumpby = cocos2d::JumpBy::create(1, cocos2d::Vec2(0, 0), 3, 1);
	cocos2d::RepeatForever *repeatforever = cocos2d::RepeatForever::create(jumpby);
	item->runAction(repeatforever);

	//create shadow
	shadow = cocos2d::Sprite::create("Item/shadow__.png");
	shadow->setAnchorPoint(cocos2d::Vec2(0, 0.5));
	shadow->setPosition(position);
	item->setVisible(true);
	Map->addChild(shadow, 1);

	cocos2d::Vector<cocos2d::SpriteFrame*> shadowArry;
	auto *frameCache1 = cocos2d::SpriteFrameCache::getInstance();
	frameCache1->addSpriteFramesWithFile("Item/shadow.plist", "Item/shadow1.png");
	for (int i = 1; i < 3; ++i)
	{
		auto *frame1 = frameCache1->getSpriteFrameByName(cocos2d::String::createWithFormat("shadow_%d.png", i)->getCString());
		shadowArry.pushBack(frame1);
	}
	cocos2d::Animation *animation1 = cocos2d::Animation::createWithSpriteFrames(shadowArry);
	animation1->setLoops(-1);
	animation1->setDelayPerUnit(0.5f);

	auto *action1 = cocos2d::Animate::create(animation1);
	shadow->runAction(action1);

	if (itemNo > 3)
	{
		auto plistFile = cocos2d::String::createWithFormat("Item/item%d.plist", itemNo);
		auto pngFile = cocos2d::String::createWithFormat("Item/item%d.png", itemNo);

		auto *frameCache = cocos2d::SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile(plistFile->getCString(), pngFile->getCString());

		cocos2d::Vector<cocos2d::SpriteFrame*> itemArry;
		for (int i = 1; i < 4; ++i)
		{
			auto *frame = frameCache->getSpriteFrameByName(cocos2d::String::createWithFormat("item%d_%d.png", itemNo, i)->getCString());
			itemArry.pushBack(frame);
		}
		cocos2d::Animation *animation = cocos2d::Animation::createWithSpriteFrames(itemArry);
		animation->setLoops(-1);
		animation->setDelayPerUnit(0.1f);

		auto *action = cocos2d::Animate::create(animation);
		item->runAction(action);
	}

	items[static_cast<int>(TPos.x)][static_cast<int>(TPos.y)] = &(*this);
	isItem[static_cast<int>(TPos.x)][static_cast<int>(TPos.y)] = itemNo;
}

/****************************************************/
void Item::remove()
{
	Map->removeChild(item);
	Map->removeChild(shadow);
}

cocos2d::CCPoint Item::getItemPosition()
{
	float x = static_cast<float>(tilePos.x) * Map->getTileSize().width;
	float y = (Map->getMapSize().height - 1 - static_cast<float>(tilePos.y)) * Map->getTileSize().height;
	return cocos2d::Vec2(x, y);
}

unsigned int randNum()
{
	static HCRYPTPROV hProvider = 0;
	static const DWORD dwLength = 2;
	static BYTE pbBuffer[dwLength] = {};

	DWORD result = ::CryptAcquireContextW(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);

	DWORD res = ::CryptGenRandom(hProvider, dwLength, pbBuffer);
	auto randomVal = *(unsigned int*)pbBuffer;

	::CryptReleaseContext(hProvider, 0);

	return randomVal;
}

void randomItem(const cocos2d::CCPoint &itemPos, cocos2d::CCTMXTiledMap* Map)
{
	if (test_model == true) {
		int itemNum = randNum() % 100;

		if (itemNum > 100 * (1 - PROBABILITY))
		{
			int itemNo = 0, itemNumber = 0;
			if (itemNum < 80)
				itemNo = itemNum % 4 + 1;
			else
				itemNo = itemNum % 3 + 5;
			if (itemNo > 0) {
				if (itemNo == 1)
					itemNumber = itemNo + randNum() % 3;
				else
					itemNumber = itemNo + 2;
			}
			auto item = new Item(itemNumber, itemPos, Map);

		}
	}
	else {
		if (fixedItems[myMapSelect - 1][static_cast<int>(itemPos.x)][static_cast<int>(itemPos.y)])
			auto item = new Item(fixedItems[myMapSelect - 1][static_cast<int>(itemPos.x)][static_cast<int>(itemPos.y)], itemPos, Map);
	}	
}
