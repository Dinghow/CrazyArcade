#ifndef __VIDEO_PLAYER__
#define __VIDEO_PLAYER__

#include "cocos2d.h"
#include "ui/UIVideoPlayer.h"
#include "ui/CocosGUI.h"


class VideoPlayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void videoPlayOverCallBack();
	void showVideo();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	void videoEventCallback(Ref* sender, cocos2d::experimental::u::VideoPlayer::EventType eventType);
#endif

	// implement the "static create()" method manually
	CREATE_FUNC(VideoPlayer);
};

#endif