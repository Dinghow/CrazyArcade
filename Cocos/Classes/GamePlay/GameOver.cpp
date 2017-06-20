#include "GameOver.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "RoomScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;
// on "init" you need to initialize your instance
bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("MapScene/OverLayer.csb");
	root = (Layout*)rootNode->getChildByName("paner");
	if (test_model == false) {
		if (opponent == 0 && isMeAlive == true)
			imag = ImageView::create("MapScene/win.png");
		else if (opponent > 0 && isMeAlive == false)
			imag = ImageView::create("MapScene/lose.png");
		else if (opponent > 0 && isMeAlive == true) {
			imag = ImageView::create("MapScene/draw.png");
		}
	}
	else if (test_model == true) {
		if (opponent == 0 && isMeAlive == true)
			imag = ImageView::create("MapScene/win.png");
		else if (opponent > 0 && isMeAlive == false)
			imag = ImageView::create("MapScene/win.png");
		else if (opponent > 0 && isMeAlive == true) {
			imag = ImageView::create("MapScene/draw.png");
		}
	}
	imag->setAnchorPoint(Vec2(0.5, 0.5));
	imag->setPosition(ccp(0, 0));
	imag->setScale(0);
	root->addChild(imag);
	time = 0.0;
	this->schedule(schedule_selector(GameOver::update), 0.1f);

	addChild(rootNode);
	imag->runAction(ScaleTo::create(0.2f, 1.0));


	return true;
}

void GameOver::update(float dt) {
	time += dt;
	if (time >= 2.5f&&time < 2.6f)
		backToMap();
}

void GameOver::backToMap() {
	this->removeFromParentAndCleanup(true);
	shouldBack = true;
}

void GameOver::onEnter() {
	Layer::onEnter();
}

void GameOver::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	//play music
}

void GameOver::onExit() {
	Layer::onExit();
}

void GameOver::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
}

void GameOver::cleanup() {
	Layer::cleanup();
}

