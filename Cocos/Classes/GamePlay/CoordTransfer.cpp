#include "CoordTransfer.h"

//transfer position coord to tile coord
CCPoint tilecoordForPosition(CCPoint position) {
	int x = 0;
	int y = 0;
	if (position.x > 0)
		x = int(position.x / theMap->getTileSize().width);
	else if (position.x < 0)
		x = -1;
	if (position.y > 0)
		y = theMap->getMapSize().height - 1 - int(position.y / theMap->getTileSize().height);
	else if (position.y < 0)
		y = -1;
	return ccp(x, y);
}

//transfer tile coord to postion coord
CCPoint positionForTileCoord(CCPoint position) {
	float x = float(position.x*theMap->getTileSize().width);
	float y = float(((theMap->getMapSize().height - 1)*theMap->getTileSize().height) - position.y*theMap->getTileSize().height);
	return ccp(x, y);
}