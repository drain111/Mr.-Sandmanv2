#include "MainMenuScene.h"
#include "GameScene.h"
#include "CharacterScene.h" 
#include <string>
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "unistd.h";
#include "sys/types.h";
#include "sys/socket.h";
#include "netdb.h";
#else
#include "io.h";
#include "WS2tcpip.h";
#endif



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
	Point center = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	i = 1;
	j = 1;
	k = 1;

	moverderecha = false;
	moverizq = false;
	arriba = false;
	rotar = false;


	addChild(_chara);
	Platform *_plataforma1 = Platform::create();
	_plataforma1->setScale(10.0);
	_plataforma1->setPosition3D(Vec3(30.0, -300.0, 0.0));
	_plataformas = Array::create();
	_plataformas->addObject( _plataforma1);
	addChild(_plataforma1);
	this->runAction(Follow::create(_chara, Rect(center.x - visibleSize.width, center.y - visibleSize.height, visibleSize.width * 2, visibleSize.height)));
	_chara->setPosition3D(Vec3(90.0, 90.0, 0));
	_chara->setScale(2.0);
	
	

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPresed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);
	
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
	auto console = Director::getInstance()->getConsole();
	console->listenOnTCP(6113);
	
	struct Console::Command changeforce = {
		"changeforce",
		"Cambia la fuerza del salto",
		[ this](int fd, const std::string& args) {
			if (args.length() == 0)
			{
				
				
			}
			else
			{				
				_chara->setforce(std::stoi(args));
			}
		} };
	

	console->addCommand(changeforce);
    return true;
	
}

void Game::update(float dt) {
	if (moverderecha) {
		_chara->setPositionX(_chara->getPositionX() - _chara->getmovement());
	}
	else {
		if (moverizq)
		{
			_chara->setPositionX(_chara->getPositionX() + _chara->getmovement());

		}
		else {
			if(rotar){
				_chara->setRotation3D(Vec3(0, j++, 0));
			}
		}
	}
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
		moverderecha = true;
			
		break;
	case EventKeyboard::KeyCode::KEY_D:
		moverizq = true;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		_chara->applyforce();
		break;
	case EventKeyboard::KeyCode::KEY_S:
		rotar = true;
		break;
		
	}


}
void Game::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event){

	_pressedKey = keycode;
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		moverderecha = false;

		break;
	case EventKeyboard::KeyCode::KEY_D:
		moverizq = false;

		break;
	case EventKeyboard::KeyCode::KEY_S:
		rotar = false;
		break;
	
	}
}