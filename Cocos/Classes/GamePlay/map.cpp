#include "map.h"

Scene* MapOfGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapOfGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MapOfGame::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("MapScene/Map.csb");
	//get map from the csb
	CCTMXTiledMap *map = (CCTMXTiledMap *)rootNode->getChildByName("map");
	//get objects layer
	CCTMXObjectGroup *objects = map->objectGroupNamed("objects");
	CCAssert(objects != NULL, "ObjectLayer not found");
	//set first spawn point
	auto spawnPoint1 = objects->objectNamed("spawnpoint1");
	int x = spawnPoint1.at("x").asInt();
	int y = spawnPoint1.at("y").asInt();

	CCTexture2D* playerTexture = CCTextureCache::sharedTextureCache()->addImage("rolePosition.png");
	CCSprite* player1 = CCSprite::createWithTexture(playerTexture);
	player1->retain();
	player1->setPosition(ccp(x, y));

	map->addChild(player1);

	addChild(rootNode);

	return true;
}
