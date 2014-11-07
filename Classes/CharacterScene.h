#ifndef __CHARACTER_SCENE_H__
#define __CHARACTER_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;


class Character : public cocos2d::Sprite
{

	PhysicsBody *_body;
	int force;

public:


	bool onContactBegin(cocos2d::PhysicsContact& contact);
	PhysicsWorld* mWorld;

	
	// there's no 'id' in cpp, so we recommend returning the class instance pointer

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	float getmovement();

	void applyforce();

	void setforce(int a);

	bool IsXBOXControlConnected();

	PhysicsBody getbody();

	// implement the "static create()" method manually
	CREATE_FUNC(Character);

	
};

#endif // __HELLOWORLD_SCENE_H__