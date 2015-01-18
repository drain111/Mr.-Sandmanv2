#include "SelectLevelScene.h"
#include "GameScene.h"
#include "Game2Scene.h"
#include "LaberintScene.h"
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
#include "MainMenuScene.h"
#include "HUD.h"

USING_NS_CC;
Sprite3D *casafinal;

Scene* Selectlevel::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = Selectlevel::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	

    // add layer as a child to scene
    scene->addChild(layer);

	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Selectlevel::init()
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
	free = true;
	moverderecha = false;
	moverizq = false;
	arriba = false;
	rotar = false;
	selecciondenivel = false;
	selectedtag = 0;
	changescene = false;
#pragma endregion
	auto sky = Sprite3D::create("char/citysky.c3b");
	sky->setPositionZ(-2000);
	sky->setPositionX(800);
	sky->setScaleX(150);
	sky->setScaleY(90);
	addChild(sky);
	camera = Camera::createPerspective(60,visibleSize.width / visibleSize.height,1, 1000);
	camera->setPosition3D(Vec3(0, 0, 500));
	_chara->setPosition3D(Vec3(0, 90.0, 0.0));
	_chara->setScale(1.0);
	camera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));
	addChild(camera);
	camera->setScale(3);
	_chara->vidas = def->getIntegerForKey("vidas");
	_houses = Array::create();
	_houses->retain();
	
	

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Selectlevel::onKeyPresed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Selectlevel::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->scheduleUpdate();



	//Physics

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Selectlevel::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	

	createhouse(0, 0);
	createhouse(800, 1);
	createhouse(1600, 2);
	createhouse(2400, 3);
	auto sprite = Sprite3D::create("char/casa.c3t");
	sprite->setScaleX(8);
	sprite->setScaleY(8);
	sprite->setScaleZ(4);
	sprite->setPosition3D(Vec3(-800, 550, -400));
	sprite->setRotation3D(Vec3(180, 90, 180));
	addChild(sprite);
	sprite->setName("sepizq");

	PhysicsBody *finalbody = PhysicsBody::createBox(Size(10, 3000), PhysicsMaterial(10, 0, 0.9f));
	finalbody->setPositionOffset(Vec2(500.0f, 0.0f));
	finalbody->setContactTestBitmask(true);
	finalbody->setDynamic(false);
	finalbody->setRotationEnable(false);
	finalbody->addMass(30.0);
	finalbody->addMoment(2.0);
	finalbody->setLinearDamping(0.8f);
	sprite->setPhysicsBody(finalbody);

	PhysicsBody *worldbody = PhysicsBody::createEdgeBox(Size(10000, 1), PhysicsMaterial(10, 0, 0.9f));
	worldbody->setPositionOffset(Vec2(0.0f, -205.0f));
	worldbody->setContactTestBitmask(true);
	worldbody->setDynamic(false);
	worldbody->setRotationEnable(false);
	worldbody->addMass(30.0);
	worldbody->addMoment(2.0);
	worldbody->setLinearDamping(0.8f);
	this->setPhysicsBody(worldbody);
	
	hud = new HUD(_chara->vidas, false,0);
	this->addChild(hud);
	__String *puntuacion = __String::createWithFormat("Puntuacion: %d", def->getIntegerForKey("puntuacion1"));
	LabelTTF *puntuacion1 = LabelTTF::create(puntuacion->getCString(), "Cryptik", 100.0f, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	addChild(puntuacion1);
	
	//xinput

	Player1 = new CXBOXController(1);

	auto console = Director::getInstance()->getConsole();
	//console->listenOnTCP(6113);
	
	struct Console::Command changeforc = {
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
	

	console->addCommand(changeforc);
    return true;
	
}
void Selectlevel::createhouse(int x, int tag) {
	auto sprite = Sprite3D::create("char/casa.c3t");
	sprite->setScaleX(8);
	sprite->setScaleY(8);
	sprite->setScaleZ(4);
	sprite->setPosition3D(Vec3(x, 550, -400));
	sprite->setRotation3D(Vec3(180, 90, 180));
	
	sprite->setName("casa");
	sprite->setTag(tag);
	addChild(sprite);

	PhysicsBody *housebody = PhysicsBody::createEdgeBox(Size(70, 5));
	housebody->setPositionOffset(Vec2(-80.0f, -756.0f));
	housebody->setContactTestBitmask(true);
	housebody->setDynamic(false);
	housebody->setRotationEnable(false);
	housebody->addMass(30.0);
	housebody->addMoment(2.0);
	housebody->setLinearDamping(0.8f);
	sprite->setPhysicsBody(housebody);

}
PhysicsWorld* Selectlevel::getPhysicsWorld() {
	return mWorld;
}

void Selectlevel::update(float dt) {
	if (moverderecha && !changescene) {
		_chara->getPhysicsBody()->applyForce(Vec2(-_chara->force, -200000));

	}
	else {
		if (moverizq  && !changescene)
		{
			_chara->getPhysicsBody()->applyForce(Vec2(_chara->force, -200000));

		}

	}

	//XINPUT 
	if (_chara->getPositionY() < -400.0f)
	{
		_chara->vidas -= 1;
		def->setIntegerForKey("vidas", _chara->vidas);
		def->flush();
		if (!def->getIntegerForKey("vidas") == 0) Restart();
	}
	if (def->getIntegerForKey("vidas") == 0) goToMainMenu();

if (Player1->IsConnected()) {
	/*//Player1->Vibrate(65535, 10);
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

		}*/
	}

if (_chara->getPositionX() > 0) {
	camera->setPosition(Vec2(_chara->getPositionX(), camera->getPositionY()));
	hud->setPositionX(300 + _chara->getPositionX());
}
if (changescene == true) {
	
	if (casafinal->getNumberOfRunningActions() == 0) GoToGameScene();
}
}
void Selectlevel::menuCloseCallback(Ref* pSender)
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
void Selectlevel::GoToPauseScene() 
{
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void Selectlevel::onKeyPresed(EventKeyboard::KeyCode keycode, Event *event){
	
	_pressedKey = keycode;
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		moverderecha = true;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		moverizq = true;
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		GoToPauseScene();
		break;
	}
	if (selecciondenivel == true && keycode == EventKeyboard::KeyCode::KEY_SPACE) {
		casafinal = dynamic_cast<Sprite3D*>(_houses->getLastObject());
		auto animation3d = Animation3D::create("char/casa.c3t");
		auto animate3d = Animate3D::create(animation3d, 0, 2);
		casafinal->runAction(animate3d);
		changescene = true;
	}
}
void Selectlevel::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event){

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
	}

}
bool Selectlevel::onContactBegin(cocos2d::PhysicsContact& contact) {
	// Do something






	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (spriteA->getName().compare("character")  == 0 &&  spriteB->getName().compare("casa") == 0) {
		selecciondenivel = true;
		selectedtag = spriteB->getTag();
		_houses->addObject(spriteB);

	}
	else {
		if (_houses->capacity() != 0) {

			_houses->removeAllObjects();
			selecciondenivel = false;
		}
	}
	free = true;
	_chara->getPhysicsBody()->setVelocityLimit(500);
	return true;
}
void Selectlevel::GoToGameScene()
{
	this->cleanup();
	Scene *scene;
	_houses->autorelease();
	switch (selectedtag)
	{ 
	case 0:
		scene = Game::createScene();

		break;
	case 1:
		scene = LABERINT::createScene();
		break;
	default:
		break;
	} 
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));

		
	
}
void Selectlevel::goToMainMenu() {
	auto scene = MainMenu::createScene();
	this->cleanup();

	_houses->autorelease();

	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, scene, 0));
}
void Selectlevel::Restart() {
	auto scene = Selectlevel::createScene();
	this->cleanup();

	_houses->autorelease();

	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, scene, 0));
}