#include "PlayScene.h"

//create animation frames
CCAnimation* MapOfGame::creatAnimationByDirecton(RoleDirection direction, cocos2d::SpriteFrameCache* cache) {
	Vector<SpriteFrame*> frames(5);
	cocos2d::SpriteFrame* frame1, *frame2, *frame3, *frame4, *frame5;
	switch (direction)
	{
	case kUp:
		frame1 = cache->getSpriteFrameByName("role/stop_up.png");
		frame2 = cache->getSpriteFrameByName("role/move_up_1.png");
		frame3 = cache->getSpriteFrameByName("role/move_up_2.png");
		frame4 = cache->getSpriteFrameByName("role/move_up_3.png");
		frame5 = cache->getSpriteFrameByName("role/move_up_4.png");
		frames.pushBack(frame1);
		frames.pushBack(frame2);
		frames.pushBack(frame3);
		frames.pushBack(frame4);
		frames.pushBack(frame5);
		break;
		/*animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_up.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_up_4.png"));
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);*/
	case kDown:
		frame1 = cache->getSpriteFrameByName("role/stop_down.png");
		frame2 = cache->getSpriteFrameByName("role/move_down_1.png");
		frame3 = cache->getSpriteFrameByName("role/move_down_2.png");
		frame4 = cache->getSpriteFrameByName("role/move_down_3.png");
		frame5 = cache->getSpriteFrameByName("role/move_down_4.png");
		frames.pushBack(frame1);
		frames.pushBack(frame2);
		frames.pushBack(frame3);
		frames.pushBack(frame4);
		frames.pushBack(frame5);
		break;
		/*animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_down.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_down_4.png"));
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);*/
	case kLeft:
		frame1 = cache->getSpriteFrameByName("role/stop_left.png");
		frame2 = cache->getSpriteFrameByName("role/move_left_1.png");
		frame3 = cache->getSpriteFrameByName("role/move_left_2.png");
		frame4 = cache->getSpriteFrameByName("role/move_left_3.png");
		frame5 = cache->getSpriteFrameByName("role/move_left_4.png");
		frames.pushBack(frame1);
		frames.pushBack(frame2);
		frames.pushBack(frame3);
		frames.pushBack(frame4);
		frames.pushBack(frame5);
		break;
		/*animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_left.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_left_4.png"));
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);*/
	case kRight:
		frame1 = cache->getSpriteFrameByName("role/stop_right.png");
		frame2 = cache->getSpriteFrameByName("role/move_right_1.png");
		frame3 = cache->getSpriteFrameByName("role/move_right_2.png");
		frame4 = cache->getSpriteFrameByName("role/move_right_3.png");
		frame5 = cache->getSpriteFrameByName("role/move_right_4.png");
		frames.pushBack(frame1);
		frames.pushBack(frame2);
		frames.pushBack(frame3);
		frames.pushBack(frame4);
		frames.pushBack(frame5);
		break;
		/*animation->addSpriteFrame(cache->getSpriteFrameByName("role/stop_right.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_1.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_2.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_3.png"));
		animation->addSpriteFrame(cache->getSpriteFrameByName("role/move_right_4.png"));
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);*/
	default:
		break;
	}
	CCAnimation* animation = new CCAnimation();
	animation->initWithSpriteFrames(frames, 0.2f);

	return animation;
}

//set face direciton
void MapOfGame::setFaceDirection(RoleDirection direction) {
	switch (direction) {
	case kUp:
		role1.role->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_up.png"));
		break;
	case kDown:
		role1.role->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_down.png"));
		break;
	case kLeft:
		role1.role->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_left.png"));
		break;
	case kRight:
		role1.role->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role/stop_right.png"));
		break;
	default:
		break;
	}
}


//the call back function of finished walk
void MapOfGame::onWalkDone(RoleDirection direction) {
	this->setFaceDirection(direction);
}

//check whether the key is pressed
bool MapOfGame::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

//the event during key pressed
void MapOfGame::keyPressedAnimation(EventKeyboard::KeyCode keyCode) {
	RoleDirection tag;
	//you can set move speed here
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		tag = kUp;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		tag = kDown;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		tag = kLeft;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		tag = kRight;
		break;
	default:
		break;
	}
	animations[tag] = RepeatForever::create(CCAnimate::create(walkAnimations[tag]));
	//animations[tag] = CCAnimate::create(walkAnimations[tag]);
	role1.role->runAction(animations[tag]);
}
void MapOfGame::keyPressedMovement(EventKeyboard::KeyCode keyCode) {
	CCPoint moveByPosition;
	RoleDirection tag;
	//you can set move speed here
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		moveByPosition = ccp(0, role1.getSpeed());
		tag = kUp;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		moveByPosition = ccp(0, -role1.getSpeed());
		tag = kDown;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		moveByPosition = ccp(-role1.getSpeed(), 0);
		tag = kLeft;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveByPosition = ccp(role1.getSpeed(), 0);
		tag = kRight;
		break;
	default:
		moveByPosition = ccp(0, 0);
		break;
	}
	//collision check
	CCPoint targetPosition = ccpAdd(role1.role->getPosition(), moveByPosition);
	if (checkCollision(role1.role->getPosition(),targetPosition, tag) == kWall&&!role1.killedOrNot()) {
		setFaceDirection(tag);
		return;
	}

	//create a action combined move action and related animation
	/*CCAction *action = CCSequence::create(
	CCSpawn::create(
	CCAnimate::create(walkAnimations[tag]),
	CCMoveBy::create(0.28f, moveByPosition), NULL)
	,CCCallFuncND::create(this, callfuncND_selector(MapOfGame::onWalkDone), (void*)(tag))
	, NULL);*/
	//auto spaw = CCSpawn::create(CCAnimate::create(walkAnimations[tag]), CCMoveBy::create(0.01f, moveByPosition), NULL);
	auto move = CCMoveBy::create(0.01f, moveByPosition);
	role1.role->runAction(move);
}
