#include "Role.h"
Role::Role() {
	bombQuantity = 5;
	bombRange = 3;
	speed = 6.5;
	for (int i = 0; i < bombQuantity; i++)
	{
		cBomb* bomb = new cBomb(bombRange);
		m_Bombs.push_back(bomb);
	}
}

void Role::loadPositon() {
	position = role->getPosition();
}

void Role::dropBomb()
{
	for (auto it : m_Bombs)
	{
		if (!it->droppedOrNot())
		{
			it->dropBomb();
			break;
		}
	}
}

void Role::addBomb()
{
	cBomb* bomb = new cBomb(bombRange);
	m_Bombs.push_back(bomb);
}

void Role::addBombRange()
{
	bombRange++;
	for (auto it : m_Bombs)
		it->addBombRange();
}