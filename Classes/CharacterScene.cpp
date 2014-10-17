#include "CharacterScene.h"
#include "GameScene.h"

USING_NS_CC;

auto vidas = 10;

Sprite* Character::createCharacter()
{
	// 'scene' is an autorelease object
	Sprite* sprite = Sprite::create("char/char.png");

	// 'layer' is an autorelease object
	// add layer as a child to scene

	// return the scene
	return sprite;
}

// on "init" you need to initialize your instance
/*bool Character::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

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


void Character::menuCloseCallback(Ref* pSender)
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
void Character::GoToGameScene(Ref* pSender)
{
	//auto scene = GameScene::createScene();

	// Director::getInstance()->replaceScene(TransitionFade::create(1.0,scene));
}
*/