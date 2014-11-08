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
	force = 500000;

	addChild(sprite);


	auto animation3d = Animation3D::create("char/char.c3t");
	auto animate3d = Animate3D::create(animation3d);
	sprite->runAction(RepeatForever::create(animate3d));
	
	
	
	
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

void Character::move(String direccion) {
	
	/*if(direccion == "izq")
	this->getPhysicsBody()->applyForce(Vec2(-force, 0), this->getPhysicsBody()->getPosition());
	if(direccion == "der")
	this->getPhysicsBody()->applyForce(Vec2(force, 0), this->getPhysicsBody()->getPosition());
	*/
}

void Character::setforce(int a) {
	force = a;
}
PhysicsBody Character::getbody() {
	return *_body;
}
Rect Character::getrect() {
	return *rectangle;
}