#include "MainMenuScene.h"
#include "GameScene.h"
#include "CharacterScene.h" 

USING_NS_CC;
Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);


    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_chara = Character::create();

	addChild(_chara);

	

	_chara->setPositionX(90.0);
	_chara->setPositionY(90.0);
	


	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPresed, this);
	//keyboardListener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);
	
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->scheduleUpdate();

	/*auto body = PhysicsBody::createCircle(chara->getContentSize().width / 2); // radius
	body->setContactTestBitmask(true);
	body->setDynamic(true);
	chara->setPhysicsBody(body);*/

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

void Game::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void Game::GoToGameScene(Ref* pSender) 
{
	//auto scene = GameScene::createScene();
    
   // Director::getInstance()->replaceScene(TransitionFade::create(1.0,scene));
}
void Game::onKeyPresed(EventKeyboard::KeyCode keycode, Event *event){
	
	_pressedKey = keycode;
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		_chara->setPositionX(_chara->getPositionX() - _chara->getmovement());
			
		break;
	}


}