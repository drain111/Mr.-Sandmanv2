#include "CharacterScene.h"
#include "GameScene.h"

USING_NS_CC;

auto vidas = 10;
auto movement = 20.0;

bool Character::init()
{

	if (!Sprite::init())
	{
		return false;
	}

	auto sprite = Sprite3D::create("char/char.c3t");
	force = 1000;

	addChild(sprite);
	auto animation3d = Animation3D::create("char/char.c3t");
	auto animate3d = Animate3D::create(animation3d);
	sprite->runAction(RepeatForever::create(animate3d));


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
	
	return true;
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
