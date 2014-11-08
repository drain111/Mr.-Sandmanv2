#ifndef __PLATFORM_SCENE_H__
#define __PLATFORM_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;


class Platform : public cocos2d::Sprite
{

	PhysicsBody *_body;
	PhysicsWorld* mWorld;
	Sprite3D *sprite;

public:





	// there's no 'id' in cpp, so we recommend returning the class instance pointer

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void GoToPlatformScene(Ref* pSender);

	void setPhysicsWorld(PhysicsWorld* world) {
		mWorld = world;
		mWorld->setGravity(Vect(0, -9));  // No gravity
	}

	PhysicsBody getbody();

	Size getsprite();


	// implement the "static create()" method manually
	CREATE_FUNC(Platform);

	
};

#endif // __HELLOWORLD_SCENE_H__