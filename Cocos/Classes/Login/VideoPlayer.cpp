#include "VideoPlayer.h"
#include "LoginScene.h"

void VideoPlayer::videoPlayOverCallBack()
{
	auto scene = Login::createScene();
	Director::getInstance()->replaceScene(scene);
}
