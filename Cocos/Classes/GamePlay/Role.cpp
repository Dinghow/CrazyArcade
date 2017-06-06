#include "Role.h"
Role::Role() {
	bombQuantity = 1;
	bombRange = 1;
	speed = 6.5;
}

void Role::setProperties(int speed, int bombRange, int bombQuantity){
	this->bombQuantity = bombQuantity;
	this->bombRange = bombRange;
	this->speed = speed;
}

void Role::loadPositon() {
	position = role->getPosition();
}