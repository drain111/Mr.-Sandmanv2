#include "MainMenuScene.h"
#include "Game2Scene.h"
#include "CharacterScene.h" 
#include <string>
#include "CXBOXController.h"
#include "PauseScene.h"
#include "DoorScene.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "unistd.h";
#include "sys/types.h";
#include "sys/socket.h";
#include "netdb.h";
#else
#include "io.h";
#include "WS2tcpip.h";
#endif
#include "SelectlevelScene.h"

USING_NS_CC;
//float rot = 0.2f;
//int direc = 0;
Scene* Game2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = Game2::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	

    // add layer as a child to scene
    scene->addChild(layer);

	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	def = CCUserDefault::sharedUserDefault();



		
	
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
	bool abrir = false;
	puntuacion = 0;
	_chara->vidas = def->getIntegerForKey("vidas");

#pragma endregion
	muerto = false;
	camera = Camera::createPerspective(60,visibleSize.width / visibleSize.height,1, 1000);
	camera->setPosition3D(Vec3(0, 0, 500));
	_plataformas = Array::create();
	_plataformas->retain();
	_chara->setPosition3D(Vec3(90.0, 90.0, 0.0));
	_chara->setScale(1.0);
	camera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));
	addChild(camera);
	camera->setScale(3);

	createplatform(100.0, -300.0, 0.0, 8000.0, 160000, 1, 32, 65, "plataforma");

	auto door1 = Door::create();
	addChild(door1); 
	

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Game2::onKeyPresed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Game2::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->scheduleUpdate();



	//Physics

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Game2::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	hud = new HUD(_chara->vidas, true,800);
	this->addChild(hud);
	
	

	
	//xinput


	auto console = Director::getInstance()->getConsole();
	//console->listenOnTCP(6113);
	
	struct Console::Command changeforce = {
		"changeforce",
		"Cambia la fuerza del salto",
		[this](int fd, const std::string& args) {
			if (args.length() == 0)
			{
				
				
			}
			else
			{			
				createplatform((int)args[0], (int)args[1], (int)args[2], (int)args[3], (int)args[4], (int)args[5], (int)args[6], (int)args[7], args);
			}
		} };
	

	console->addCommand(changeforce);
    return true;
	
}
PhysicsWorld* Game2::getPhysicsWorld() {
	return mWorld;
}
void Game2::createplatform(double x, double y, double z, double scale, double bodyscalex, double bodyscaley, double xoffset, double yoffset, std::string name){
	
	//create platform
	Platform *_plataforma = Platform::create();
	_plataforma->setScaleX(scale);
	_plataforma->setScaleY(10);
	_plataforma->setName(name);
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
void Game2::update(float dt) {
	if (moverizq && free) {
		//_chara->setPositionX(_chara->getPositionX() - _chara->getmovement());
		_chara->getPhysicsBody()->applyForce(Vec2(-_chara->force, -200000));

	}
	else {
		if (moverderecha && free)
		{
			//_chara->setPositionX(_chara->getPositionX() + _chara->getmovement());
			_chara->getPhysicsBody()->applyForce(Vec2(_chara->force, -200000));

		}
		

	}
		//auto *aux = dynamic_cast<Platform*>(_plataformas->getObjectAtIndex(0));


		//aux->setPositionX(aux->getPositionX() + 1);


		if (_chara->getPhysicsBody()->getVelocity().y == 0) {
			free = true;
			_chara->getPhysicsBody()->setVelocityLimit(400);

		}
	
	//XINPUT 
		if (_chara->getPositionY() < -400.0f && muerto == false)
		{
			muerto = true;
			_chara->vidas -= 1;
			def->setIntegerForKey("vidas", _chara->vidas);
			if (!def->getIntegerForKey("vidas") == 0) Restart();
			else {
				GotoMenuScene();
			}
		}

hud->update();
camera->setPosition3D(Vec3(_chara->getPositionX(), camera->getPositionY(), camera->getPositionZ()));
hud->setPositionX(300 + _chara->getPositionX());

	
}
void Game2::menuCloseCallback(Ref* pSender)
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
void Game2::GoToPauseScene() 
{
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void Game2::onKeyPresed(EventKeyboard::KeyCode keycode, Event *event){
	auto *aux = dynamic_cast<Platform*>(_plataformas->getLastObject());
	
	_pressedKey = keycode;
	if (free)
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_D:
		moverderecha = true;
		_chara->runanimation();
		break;
	case EventKeyboard::KeyCode::KEY_A:
		moverizq = true;
		_chara->runanimation();

		break;
	case EventKeyboard::KeyCode::KEY_W:
		
			_chara->getPhysicsBody()->setVelocityLimit(700);
			_chara->jumpanimation();
			if (moverizq) {
				_chara->getPhysicsBody()->resetForces();

				_chara->jumpright();
			}
			else if (moverderecha) {
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
		case EventKeyboard::KeyCode::KEY_D:
			_chara->getPhysicsBody()->applyForce(Vec2(_chara->force, 0));
			break;
		case EventKeyboard::KeyCode::KEY_A:
			_chara->getPhysicsBody()->applyForce(Vec2(-_chara->force, 0));
			break;
		case EventKeyboard::KeyCode::KEY_Q:
			GoToPauseScene();
			break;
		}
		
		
	}
}
void Game2::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event){

	_pressedKey = keycode;
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_D:
		moverderecha = false;
		_chara->getPhysicsBody()->resetForces();

		break;
	case EventKeyboard::KeyCode::KEY_A:
		moverizq = false;
		_chara->getPhysicsBody()->resetForces();
		break;
	case EventKeyboard::KeyCode::KEY_S:
		rotar = false;
		break;
	
	
	}

}
bool Game2::onContactBegin(cocos2d::PhysicsContact& contact) {
	// Do something






	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	
	if ((spriteA->getName().compare("esfera") == 0 || spriteA->getName().compare("character") == 0) && (spriteB->getName().compare("esfera") == 0 || spriteB->getName().compare("character") == 0)) {
		GotoMenuScene();
	}
	return true;
}
void Game2::GotoMenuScene()
{
	if (_chara->vidas != 0) {
	puntuacion = _chara->vidas * hud->tiempo;
	def->setIntegerForKey("puntuacion1", puntuacion);
	}
	else {
		_chara->vidas = 3;

	}
	def->setIntegerForKey("vidas", _chara->vidas);

	def->flush();

	auto scene = Selectlevel::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}
void Game2::Restart() {
	auto scene = Game2::createScene();

	Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0, scene));

}