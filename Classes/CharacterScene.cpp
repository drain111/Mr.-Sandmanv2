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
	force = 900000;

	addChild(sprite);

	setName("character");

	auto animation3d = Animation3D::create("char/char.c3t");
	auto animate3d = Animate3D::create(animation3d);
	sprite->runAction(RepeatForever::create(animate3d));
	auto _body1 = PhysicsBody::createCircle(30, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(3, 3)); // radius
	_body1->setContactTestBitmask(true);
	_body1->setDynamic(true);
	_body1->setRotationEnable(false);
	_body1->addMass(30.0);
	_body1->addMoment(0);
	_body1->setVelocityLimit(500);

	_body1->setPositionOffset(Vec2(0, 50));
	setPhysicsBody(_body1);
	
	
	
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

float Character::getmovement() {
	return movement;
}
void Character::jump() {

	this->getPhysicsBody()->applyImpulse(Vec2(0, force), this->getPhysicsBody()->getPosition());
	
}
void Character::jumpright() {

	this->getPhysicsBody()->applyImpulse(Vec2(-2*force, 2*force), this->getPhysicsBody()->getPosition());

}
void Character::jumpleft() {

	this->getPhysicsBody()->applyImpulse(Vec2(2 * force, 2 * force), this->getPhysicsBody()->getPosition());

}
void Character::move(String direccion) {
	
	/*if(direccion.compare("izq"))
	this->getPhysicsBody()->applyForce(Vec2(-force, 0), this->getPhysicsBody()->getPosition());
	if(direccion.compare("der"))
	this->getPhysicsBody()->applyForce(Vec2(force, 0), this->getPhysicsBody()->getPosition());
	*/
}

void Character::setforce(int a) {
	force = a;
}
PhysicsBody Character::getbody() {
	return *_body;
}
