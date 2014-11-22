#include "MainMenuScene.h"
#include "GameScene.h"
#include "CharacterScene.h" 
#include <string>
#include "CXBOXController.h"
#include "PauseScene.h"
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
	
	
#pragma region Creaciondevariables

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

#pragma endregion

	

	Platform *_plataforma1 = Platform::create();
	_plataforma1->setScale(10.0);
	_plataforma1->setPosition3D(Vec3(30.0, -300.0, 0.0));
	_plataformas = Array::create();
	_plataformas->retain();
	_plataformas->addObject(_plataforma1);
	this->runAction(Follow::create(_chara, Rect(center.x - visibleSize.width, center.y - visibleSize.height, visibleSize.width * 4, visibleSize.height )));
	_chara->setPosition3D(Vec3(90.0, 90.0, 0.0));
	_chara->setScale(2.0);
	
	
	
	

	auto _body = PhysicsBody::createEdgeBox(Size(2000, 1), PhysicsMaterial(10, 0, 0.9f),1.0, Vec2(0, 100));

	_body->setContactTestBitmask(true);
	_body->setDynamic(false);
	_body->setRotationEnable(false);
	_body->addMass(30.0);
	_body->addMoment(2.0);
	_body->setLinearDamping(0.8f);
	_plataforma1->setPhysicsBody(_body);
	addChild(_plataforma1);

	createplatform(30.0, 0.0, 0.0, 5.0, 100, 1, 22, 38);




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

	Player1 = new CXBOXController(1);
	
	/*auto Start = MenuItemImage::create("mainmenu/start.png", "mainmenu/start(click).png", CC_CALLBACK_1(Game::GoToPauseScene, this));
	auto menu = Menu::create(Start, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 2);
	this->addChild(menu, 1);*/

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
void Game::createplatform(double x, double y, double z, double scale, double bodyscalex, double bodyscaley, double xoffset, double yoffset){
	
	//create platform
	Platform *_plataforma = Platform::create();
	_plataforma->setScale(scale);
	_plataforma->setName("plataforma");
	_plataforma->setPosition3D(Vec3(x, y, z));
	_plataformas->addObject(_plataforma);


	//create body
	auto _body = PhysicsBody::createEdgeBox(Size(bodyscalex, bodyscaley), PhysicsMaterial(10, 0, 0.9f), 1.0, Vec2(xoffset, yoffset));

	_body->setContactTestBitmask(true);
	_body->setDynamic(false);
	_body->setRotationEnable(false);
	_body->addMass(30.0);
	_body->addMoment(2.0);
	_body->setLinearDamping(0.8f);
	_plataforma->setPhysicsBody(_body);
	addChild(_plataforma);

}
void Game::update(float dt) {
	if (moverderecha && free) {
		//_chara->setPositionX(_chara->getPositionX() - _chara->getmovement());
		_chara->getPhysicsBody()->applyForce(Vec2(-_chara->force, -200000));

	}
	else {
		if (moverizq && free)
		{
			//_chara->setPositionX(_chara->getPositionX() + _chara->getmovement());
			_chara->getPhysicsBody()->applyForce(Vec2(_chara->force, -200000));

		}
		else {

			if(rotar){
				_chara->setRotation3D(Vec3(0, j++, 0));
			}
		}

	}
		auto *aux = dynamic_cast<Platform*>(_plataformas->getObjectAtIndex(1));


		aux->setPositionX(aux->getPositionX() + 1);
		
		if (_chara->getPhysicsBody()->getVelocity().y == 0) {
			free = true;
			_chara->getPhysicsBody()->setVelocityLimit(500);

		}
	
	//XINPUT 


if (Player1->IsConnected()) {
	//Player1->Vibrate(65535, 10);
		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{

			moverderecha = true;
		}
		
		else if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) {

			moverizq = true;

		}
		
		else if (!Player1->GetState().Gamepad.wButtons & XINPUT_KEYSTROKE_KEYDOWN)
		{
			moverderecha = false;
			moverizq = false;
			_chara->getPhysicsBody()->resetForces();

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
void Game::GoToPauseScene() 
{
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void Game::onKeyPresed(EventKeyboard::KeyCode keycode, Event *event){
	
	_pressedKey = keycode;
	if (free)
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		moverderecha = true;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		moverizq = true;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		
			_chara->getPhysicsBody()->setVelocityLimit(800);

			if (moverderecha) {
				_chara->getPhysicsBody()->resetForces();

				_chara->jumpright();
			}
			else if (moverizq) {
				_chara->getPhysicsBody()->resetForces();

				_chara->jumpleft();
			}
			else {
				_chara->jump();
			}
			free = false;
		
		break;
	case EventKeyboard::KeyCode::KEY_S:
		rotar = true;
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		GoToPauseScene();
		break;
	}
	else
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_A:
			_chara->getPhysicsBody()->applyForce(Vec2(-_chara->force, 0));
			break;
		case EventKeyboard::KeyCode::KEY_D:
			_chara->getPhysicsBody()->applyForce(Vec2(_chara->force, 0));
			break;
		case EventKeyboard::KeyCode::KEY_Q:
			GoToPauseScene();
			break;
		}
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

}
bool Game::onContactBegin(cocos2d::PhysicsContact& contact) {
	// Do something






	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (spriteA->getName().compare("character") == 0 && spriteB->getName().compare("plataforma") == 0) {
		_chara->setPositionX(_chara->getPositionX() + 1);

	}
	
	return true;
}