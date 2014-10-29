#include "CharacterScene.h"
#include "GameScene.h"

USING_NS_CC;

auto vidas = 10;
auto movement = 20.0;

// on "init" you need to initialize your instance
bool Character::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Sprite::init())
	{
		return false;
	}

	auto sprite = Sprite3D::create("char/a.obj");
	sprite->setTexture("char/char.png");
	force = 1000;

	addChild(sprite);
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Character::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	_body = PhysicsBody::createCircle(this->getContentSize().width / 2); // radius
	_body->setContactTestBitmask(true);
	_body->setDynamic(true);
	_body->setRotationEnable(false);
	_body->addMass(30.0);
	_body->addMoment(2.0);
	this->setPhysicsBody(_body);


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
bool Character::onContactBegin(cocos2d::PhysicsContact& contact) {
	// Do something

	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (spriteA->getName().compare("A") == 0 && spriteB->getName().compare("B") == 0) {
	}

	return true;
}
float Character::getmovement() {
	return movement;
}
void Character::applyforce() {
	
	_body->applyImpulse(Vec2(0, force), _body->getPosition());
	
}
void Character::setforce(int a) {
	force = a;
}
