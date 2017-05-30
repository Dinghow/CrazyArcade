#include "Role.h"
Role::Role() {
	bombQuantity = 1;
	bombRange = 1;
	speed = 6.5;
}

void Role::loadPositon() {
	position = role->getPosition();
}