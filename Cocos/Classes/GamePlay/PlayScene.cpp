#include "PlayScene.h"

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
	map = (CCTMXTiledMap *)rootNode->getChildByName("map");
	//get objects layer
	CCTMXObjectGroup *objects = map->objectGroupNamed("objects");
	CCAssert(objects != NULL, "ObjectLayer not found");
	//set first spawn point
	auto spawnPoint1 = objects->objectNamed("spawnpoint1");
	int startX = spawnPoint1.at("x").asInt();
	int startY = spawnPoint1.at("y").asInt();

	//load the plist file
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/bazzi.plist");
	//creat the animation of four direction
	for (int i = 0; i < kTotal; i++) {
		walkAnimations[i] = creatAnimationByDirecton((RoleDirection)i);
	}

	//create the role and set the first frame as the static condition
	role1 = CCSprite::createWithSpriteFrame(((CCAnimationFrame*)(walkAnimations[kDown]->getFrames()->objectAtIndex(0)))->getSpriteFrame());
	role1->setAnchorPoint(CCPointZero);
	role1->setPosition(startX, startY);
	this->addChild(role1);

	//add the control menu of four direction
	CCMenuItem* up = CCMenuItemFont::create("up", this, menu_selector(MapOfGame::menuCallbackMove));
	CCMenuItem* down = CCMenuItemFont::create("down", this, menu_selector(MapOfGame::menuCallbackMove));
	CCMenuItem* left = CCMenuItemFont::create("left", this, menu_selector(MapOfGame::menuCallbackMove));
	CCMenuItem* right = CCMenuItemFont::create("right", this, menu_selector(MapOfGame::menuCallbackMove));
	CCMenu* menu = CCMenu::create(up, down, left, right, NULL);

	//add tag for the menu item to help search
	up->setTag(kUp);
	down->setTag(kDown);
	left->setTag(kLeft);
	right->setTag(kRight);
	
	menu->alignItemsHorizontallyWithPadding(30);
	this->addChild(menu);

	this->isRoleWalking = false;

	this->addChild(rootNode);

	return true;
}

void MapOfGame::menuCallbackMove(CCObject *pSender) {
	//"close" menu item clicked
	CCDirector::sharedDirector()->end();
}


//create animation frames
CCAnimation* MapOfGame::creatAnimationByDirecton(RoleDirection direction) {

}

//set the call back function 
void MapOfGame::menuCallbackMove(CCObject *pSender) {
	if (this->isRoleWalking)
		return;
	CCNode* node = (CCNode*)pSender;
	RoleDirection tag = (RoleDirection)node->getTag();
	CCPoint moveByPosition;
	switch (tag) {
	case kUp:
		moveByPosition = ccp(0, 20);
	case kDown:
		moveByPosition = ccp(0, -20);
	case kLeft:
		moveByPosition = ccp(-20, 0);
	case kRight:
		moveByPosition = ccp(20, 0);
		break;
	}
	CCPoint targetPosition = ccpAdd(role1->getPosition(), moveByPosition);
	//collision check
	if (checkCollision(targetPosition) == kWall) {
		setFaceDirection(tag);
		return;
	}
	CCAction *action = CCSequence::create(
		CCSpawn::create(
			CCAnimate::create(walkAnimations[tag]),
			CCMoveBy::create(0.28f, moveByPosition), NULL),								    
		CCCallFuncND::create(this, callfuncND_selector(MapOfGame::onWalkDone), (void*)(tag)), NULL);
	role1->runAction(action);
	this->isRoleWalking = true;
}

//set face direciton
void MapOfGame::setFaceDirection(RoleDirection) {

}

//the call back function of finished walk
void MapOfGame::onWalkDone(CCNode *pTarget, void *data) {
	this->isRoleWalking = false;
	RoleDirection direction = (RoleDirection)(int)data;
	this->setFaceDirection(direction);
}

//coord transfer
CCPoint MapOfGame::tilecoordForPosition(CCPoint position) {
	int x = int(position.x / map->getTileSize().width);
	int y = int(position.y / map->getTileSize().height);
	return ccp(x, y);
}

CCPoint MapOfGame::positionForTileCoord(CCPoint position) {
	float x = float(position.x*map->getTileSize().width);
	float y = float(position.y*map->getTileSize().height);
	return ccp(x, y);
}

//collision check according to the role's position
MapOfGame::CollisionType MapOfGame::checkCollision(cocos2d::CCPoint rolePosition) {
	//transfer the coord
	CCPoint tileCoord = tilecoordForPosition(rolePosition);
	//check the border of map
	if (tileCoord.x<0 || tileCoord.x>map->getMapSize().width - 1 || tileCoord.y<0 || tileCoord.y>map->getMapSize().height - 1) {
		return kWall;
	}
	if (map->layerNamed("wall")->tileGIDAt(tileCoord)) {
		return kWall;
	}
	else {
		return kNone;
	}
}

MapOfGame::~MapOfGame() {
	for (int i = 0; i < 4; i++) {
		CC_SAFE_RELEASE(walkAnimations[i]);
	}
	this->unscheduleAllSelectors();
}
