#include "Item.h"
#include <ctime>

int isItem[15][13] = { 0 };
Item* items[15][13] = { nullptr };

Item::Item(int &itemno, const cocos2d::CCPoint &TPos, cocos2d::CCTMXTiledMap* m_Map) :tilePos(TPos), Map(m_Map)
{
	cocos2d::Node::onEnter();

	if (itemno == 1)
		itemNo = itemno + randNum() % 3;
	else
		itemNo = itemno + 2;

	//create item
	auto position = getItemPosition();
	auto itemName = cocos2d::String::createWithFormat("Item/item%d__.png", itemNo);
	item = cocos2d::Sprite::create(itemName->getCString());
	item->setAnchorPoint(cocos2d::Vec2(0, 0));
	item->setPosition(position);
	item->setVisible(true);
	Map->addChild(item, 2.5);

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
	int itemNum = randNum() % 100;

	int itemNo = itemNum % 5;
	//CCLOG("%ditem:%d", itemNum, itemNo);
	if ((itemNum > 100 * (1 - PROBABILITY)) && itemNo)
		auto item = new Item(itemNo, itemPos, Map);
}