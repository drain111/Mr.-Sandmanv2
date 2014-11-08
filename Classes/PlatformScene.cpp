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
	



	


	//auto Start = MenuItemImage::create("mainmenu/start.png", "mainmenu/start(click).png", CC_CALLBACK_1(MainMenu::GoToGameScene,this));

	//auto Load = MenuItemImage::create("mainmenu/load.png", "mainmenu/load(click).png", CC_CALLBACK_1(MainMenu::GoToGameScene,this));

	//auto Exit = MenuItemImage::create("mainmenu/exit.png", "mainmenu/exit(click).png", CC_CALLBACK_1(MainMenu::GoToGameScene,this));

	//auto menu = Menu::create(Start, Load, Exit, NULL);

	//menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	// this->addChild(menu, 1);

	//auto bg = Sprite::create("mainmenu/bg.png");

	//bg->setPosition(Point((visibleSize.width/2), (visibleSize.height/2)));

	//this->addChild(bg, 0);

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object


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

