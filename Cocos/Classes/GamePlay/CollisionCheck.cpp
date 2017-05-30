#include "PlayScene.h"

//collision check according to the role's position
MapOfGame::CollisionType MapOfGame::checkCollision(cocos2d::CCPoint targetPosition, RoleDirection direction) {
	CCPoint searchRange = ccp(0, 0);
	//set search range for four directioin
	switch (direction)
	{
	case kUp:
		searchRange = ccp(0, 5);
		break;
	case kDown:
		searchRange = ccp(0, -28);
		break;
	case kLeft:
		searchRange = ccp(-20, 0);
		break;
	case kRight:
		searchRange = ccp(15, 0);
		break;
	default:
		break;
	}
	targetPosition += searchRange;
	//transfer the coord
	CCPoint tileCoord;
	//check the border of map
	if (targetPosition.x<0 || targetPosition.x>map->getMapSize().width*map->getTileSize().width
		|| targetPosition.y<0 || targetPosition.y>map->getMapSize().height*map->getTileSize().height) {
		return kWall;
	}
	//check the obstacles
	if (direction == kUp || direction == kDown) {
		for (int i = 0, j = -1; i < 2; i++, j *= -1) {
			searchRange = ccp(20 * j, 0);
			targetPosition += searchRange;
			tileCoord = tilecoordForPosition(targetPosition);
			if (map->layerNamed("architecture-real")->tileGIDAt(tileCoord)) {
				return kWall;
			}
		}
	}
	else if (direction == kLeft || direction == kRight) {
		for (int i = 0, j = -1; i < 2; i++, j *= -1) {
			searchRange = ccp(0, 28 * j);
			targetPosition += searchRange;
			tileCoord = tilecoordForPosition(targetPosition);
			if (map->layerNamed("architecture-real")->tileGIDAt(tileCoord)) {
				return kWall;
			}
		}
	}

	return kNone;
}