#ifndef __DOOR_SCENE_H__
#define __DOOR_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;


class Door : public cocos2d::Sprite
{

	PhysicsBody *_body;
	PhysicsWorld* mWorld;
	Node *puerta;

public:


	Sprite3D *sprite;



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

	void sethijo(Door *hijo);


	// implement the "static create()" method manually
	CREATE_FUNC(Door);

	
};

#endif // __HELLOWORLD_SCENE_H__