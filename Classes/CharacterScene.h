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

	virtual bool init();


	float getmovement();

	void applyforce();

	void setforce(int a);

	PhysicsBody getbody();

	// implement the "static create()" method manually
	CREATE_FUNC(Character);



	
};

#endif // __HELLOWORLD_SCENE_H_