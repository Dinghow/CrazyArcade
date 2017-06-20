#include "PlayScene.h"
#include"Player.h"
#include "CoordTransfer.h"

//collision check according to the role's position
CollisionType checkCollision(cocos2d::CCPoint rolePosition, cocos2d::CCPoint targetPosition, RoleDirection direction) {
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
	auto roleTilePosition = tilecoordForPosition(rolePosition);
	targetPosition += searchRange;
	//transfer the coord
	CCPoint tileCoord;
	//check the border of map
	if (targetPosition.x<0 || targetPosition.x>theMap->getMapSize().width*theMap->getTileSize().width
		|| targetPosition.y<0 || targetPosition.y>theMap->getMapSize().height*theMap->getTileSize().height) {
		return kWall;
	}
	//check the obstacles
	//added bombs
	if (direction == kUp || direction == kDown) {
		for (int i = 1, j = -1; i <= 2; i++, j *= -1) {
			if(targetPosition.x <= 13.5)
				break;
			searchRange = ccp(13.5* j*i, 0);
			targetPosition += searchRange;
			tileCoord = tilecoordForPosition(targetPosition);
			if (theMap->layerNamed("architecture-real")->tileGIDAt(tileCoord)) {
				return kWall;
			}
			//bomb check
			for (int i = 0; i < 2; i++)
			{
				for (auto it :m_Roles[i]->m_Bombs)
				{
					if (it->droppedOrNot())
					{
						auto bombTilePosition = tilecoordForPosition(it->bombOpenglCoord());
						if (roleTilePosition == bombTilePosition)
							continue;
						else if (tileCoord == bombTilePosition)
							return kWall;
					}
				}
			}
		}
	}
	else if (direction == kLeft || direction == kRight) {
		for (int i = 1 ; i <= 2 ; i++) {
			if (targetPosition.y < 27.6)
				break;
			if (i == 1)
				searchRange = ccp(0, -27);
			if (i == 2)
				searchRange = ccp(0, 29);
			targetPosition += searchRange;
			tileCoord = tilecoordForPosition(targetPosition);
			if (theMap->layerNamed("architecture-real")->tileGIDAt(tileCoord)) {
				return kWall;
			}
		}
		//bomb check
		for (int i = 0; i < 2; i++)
		{
			for (auto it :m_Roles[i]->m_Bombs)
			{
				if (it->droppedOrNot())
				{
					auto bombTilePosition = tilecoordForPosition(it->bombOpenglCoord());
					if (roleTilePosition == bombTilePosition)
						continue;
					else if (tileCoord == bombTilePosition)
						return kWall;
				}
			}
		}
	}

	return kNone;
}