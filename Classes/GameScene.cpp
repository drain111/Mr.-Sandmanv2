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
#include "SelectlevelScene.h"

USING_NS_CC;
float rot = 0.2f;
int direc = 0;
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

	createplatform(100.0, -230.0, 0.0, 8.0, 160, 1, 32, 65, "plataforma");

	createplatform(-152.0, 64.0, 0.0, 8.0, 160, 1, 32, 65, "plataforma");

	createplatform(-1370.0, 50.0, 0.0, 8.0, 160, 1, 32, 65, "plataforma");

	createplatform(-2200.0, 50.0, 0.0, 8.0, 160, 1, 32, 65, "plataforma");

	createplatform(-2600.0, -300.0, 0.0, 16.0, 310, 1, 70, 130, "plataforma");

	createplatform(-3980.0, -300.0, 300.0, 90.0, 1000, 1000, 800, 130, "pared");

	createplatform(-3400.0, -300.0, 0.0, 8.0, 160, 1, 32, 65, "plataforma");
	esfera = Sprite3D::create("char/esfera.c3t");
	esfera->setPosition3D(Vec3(-3300.0, 200.0, 0));
	auto _bodyesf = PhysicsBody::createCircle(128, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(-80, -80));
	esfera->setScale(4);
	_bodyesf->setContactTestBitmask(true);
	_bodyesf->setDynamic(false);
	_bodyesf->setRotationEnable(false);
	_bodyesf->addMass(30.0);
	
	
	esfera->setName("esfera");
	esfera->setPhysicsBody(_bodyesf);
	addChild(esfera);

	//create platform
	auto caja = Sprite3D::create("char/caja.obj");
	caja->setTexture("char/cubo.png");


	caja->setName("cubo");
	caja->setPosition3D(Vec3(-2200.0, 600.0, 0));

	
	//create body
	auto _body = PhysicsBody::createCircle(24, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(-16, 6));

	_body->setContactTestBitmask(true);
	_body->setDynamic(true);
	_body->setRotationEnable(false);
	_body->addMass(30.0);


	caja->setPhysicsBody(_body);
	addChild(caja);

	auto interruptor = Sprite3D::create("char/a.obj");
	interruptor->setTexture("char/plat.png");
	interruptor->setScaleX(2);
	interruptor->setName("interruptor");
	interruptor->setPosition3D(Vec3(-2500.0, -170.0, 0.0));
	auto _bodyint = PhysicsBody::createEdgeBox(Size(40, 10), PHYSICSBODY_MATERIAL_DEFAULT, 1.0F, Vec2(-10, 3));

	_bodyint->setContactTestBitmask(true);
	_bodyint->setDynamic(false);
	_bodyint->setRotationEnable(false);
	_bodyint->addMass(30.0);


	interruptor->setPhysicsBody(_bodyint);
	addChild(interruptor);


	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPresed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->scheduleUpdate();



	//Physics

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	hud = new HUD(_chara->vidas, true);
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
PhysicsWorld* Game::getPhysicsWorld() {
	return mWorld;
}
void Game::createplatform(double x, double y, double z, double scale, double bodyscalex, double bodyscaley, double xoffset, double yoffset, std::string name){
	
	//create platform
	Platform *_plataforma = Platform::create();
	_plataforma->setScale(scale);
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
	auto *aux = dynamic_cast<Platform*>(_plataformas->getLastObject());

	_pressedKey = keycode;
	if (free)
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_D:
		moverderecha = true;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		moverizq = true;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		
			_chara->getPhysicsBody()->setVelocityLimit(700);

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
		case EventKeyboard::KeyCode::KEY_D:
			_chara->getPhysicsBody()->applyForce(Vec2(-_chara->force, 0));
			break;
		case EventKeyboard::KeyCode::KEY_A:
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
bool Game::onContactBegin(cocos2d::PhysicsContact& contact) {
	// Do something






	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (spriteA->getName().compare("cubo")  == 0 && spriteB->getName().compare("interruptor") == 0) {
		spriteB->setPosition(Vec2(spriteB->getPositionX(), spriteB->getPositionY()-100));
		removeChild(dynamic_cast<Platform*>(_plataformas->getObjectAtIndex(5)));
	}
	if ((spriteA->getName().compare("esfera") == 0 || spriteA->getName().compare("character") == 0) && (spriteB->getName().compare("esfera") == 0 || spriteB->getName().compare("character") == 0)) {
		GotoMenuScene();
	}
	return true;
}
void Game::GotoMenuScene()
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
void Game::Restart() {
	auto scene = Game::createScene();

	Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0, scene));

}