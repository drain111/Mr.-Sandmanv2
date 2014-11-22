#include "PlatformScene.h"
#include "GameScene.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool Platform::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Sprite::init())
	{
		return false;
	}

	sprite = Sprite3D::create("char/a.obj");
	sprite->setTexture("char/plat.png");


	addChild(sprite);

	return true;
}


void Platform::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
Size Platform::getsprite() {
	return sprite->getContentSize();
}

