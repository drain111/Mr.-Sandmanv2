#include "MainMenuScene.h"
#include "GameScene.h"
#include "CharacterScene.h" 
#include <string>
#include "CXBOXController.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "unistd.h";
#include "sys/types.h";
#include "sys/socket.h";
#include "netdb.h";
#else
#include "io.h";
#include "WS2tcpip.h";
#endif


//CXBOXController* Player1;

USING_NS_CC;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    
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
	
	
	
	/*auto body2 = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body2);
	this->addChild(edgeNode);*/
	
	
	_chara = Character::create();
	addChild(_chara);

	Point center = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	i = 1;
	j = 1;
	k = 1;
	free = true;

	moverderecha = false;
	moverizq = false;
	arriba = false;
	rotar = false;

	

	Platform *_plataforma1 = Platform::create();
	_plataforma1->setScale(10.0);
	_plataforma1->setPosition3D(Vec3(30.0, -300.0, 0.0));
	_plataformas = Array::create();
	_plataformas->addObject( _plataforma1);
	this->runAction(Follow::create(_chara, Rect(center.x - visibleSize.width, center.y - visibleSize.height, visibleSize.width * 2, visibleSize.height)));
	_chara->setPosition3D(Vec3(90.0, 90.0, 0.0));
	_chara->setScale(2.0);
	
	auto _body1 = PhysicsBody::createCircle(60, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(3,3)); // radius
	_body1->setContactTestBitmask(0);
	_body1->setDynamic(true);
	_body1->setRotationEnable(false);
	_body1->addMass(30.0);
	_body1->addMoment(0);
	_body1->setVelocityLimit(500);
	
	_body1->setPositionOffset(Vec2(0, 50));
	_chara->setPhysicsBody(_body1);
	
	

	auto _body = PhysicsBody::createEdgeBox(Size(2000, 200), PhysicsMaterial(10, 0, 0.9));

	_body->setContactTestBitmask(0);
	_body->setDynamic(false);
	_body->setRotationEnable(false);
	_body->addMass(30.0);
	_body->addMoment(2.0);
	_body->setLinearDamping(0.8);
	_plataforma1->setPhysicsBody(_body);
	addChild(_plataforma1);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPresed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);
	
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->scheduleUpdate();




	//Physics

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	

	//xinput

	//Player1 = new CXBOXController(1);
	
	
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
PhysicsWorld* Game::getPhysicsWorld() {
	return mWorld;
}
void Game::update(float dt) {
	if (moverderecha) {
		//_chara->setPositionX(_chara->getPositionX() - _chara->getmovement());
		_chara->getPhysicsBody()->applyForce(Vec2(-_chara->force, 0));


	}
	else {
		if (moverizq)
		{
			//_chara->setPositionX(_chara->getPositionX() + _chara->getmovement());
			_chara->getPhysicsBody()->applyForce(Vec2(_chara->force, 0));

		}
		else {
			if(rotar){
				_chara->setRotation3D(Vec3(0, j++, 0));
			}
		}

	}

	if (_chara->getPhysicsBody()->getVelocity().y == 0) free = true;
	
	//XINPUT 


/*	if (Player1->IsConnected()) {
		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			moverderecha = true;
		}
		else {
			moverderecha = false;

		}
		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			moverizq = true;
		}
		else {
			moverizq = false;

		}
	}*/



	
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
		if (free)
		{
			_chara->jump();
			free = false;
		}
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
		_chara->getPhysicsBody()->resetForces();

		break;
	case EventKeyboard::KeyCode::KEY_D:
		moverizq = false;
		_chara->getPhysicsBody()->resetForces();
		break;
	case EventKeyboard::KeyCode::KEY_S:
		rotar = false;
		break;
	
	
	}

	/*if (Player1->IsConnected()) {
		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			moverderecha = false;

		}
	}*/
}
bool Game::onContactBegin(cocos2d::PhysicsContact& contact) {
	// Do something

	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (spriteA->getName().compare("A") == 0 && spriteB->getName().compare("B") == 0) {
		
	}
	
	free = true;

	return true;
}