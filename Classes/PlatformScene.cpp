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

	auto sprite = Sprite3D::create("char/a.obj");
	sprite->setTexture("char/plat.png");

	addChild(sprite);
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Platform::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	_body = PhysicsBody::createCircle(this->getContentSize().width / 2); // radius
	_body->setContactTestBitmask(true);
	_body->setDynamic(false);
	_body->setRotationEnable(false);
	_body->addMass(30.0);
	_body->addMoment(2.0);
	this->setPhysicsBody(_body);

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
bool Platform::onContactBegin(cocos2d::PhysicsContact& contact) {
	// Do something

	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (spriteA->getName().compare("A") == 0 && spriteB->getName().compare("B") == 0) {
	}

	return true;
}
