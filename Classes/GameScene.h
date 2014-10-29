#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "CharacterScene.h"

class Game : public cocos2d::Layer
{
	cocos2d::EventKeyboard::KeyCode _pressedKey;
	bool moverderecha = false;
	bool moverizq = false;
	bool arriba = false;

	int i;
	int j;
	int k;

public:
	
	Character *_chara;

	void setPhysicsWorld(cocos2d::PhysicsWorld* world) {
		mWorld = world;
		mWorld->setGravity(cocos2d::Vect(0, -9));  // No gravity
	}

	bool onContactBegin(cocos2d::PhysicsContact& contact);
	cocos2d::PhysicsWorld* mWorld;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void GoToGameScene(Ref* pSender);

	void onKeyPresed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void update(float dt);


	struct Command {
		std::string name;
		std::string help;
		std::function<void(int, const std::string&)> callback;
	};

    // implement the "static create()" method manually
    CREATE_FUNC(Game);

};

#endif // __HELLOWORLD_SCENE_H__