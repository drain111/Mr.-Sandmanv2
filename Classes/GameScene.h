#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

USING_NS_CC;


#include "cocos2d.h"
#include "CharacterScene.h"
#include "PlatformScene.h"
#include "CXBOXController.h"

class Game : public cocos2d::Layer
{
	EventKeyboard::KeyCode _pressedKey;
	bool moverderecha;
	bool moverizq;
	bool arriba;
	bool rotar;
	cocos2d::Array *_plataformas;
	int i;
	int j;
	int k;
	bool free;
	CXBOXController* Player1;


public:
	
	Character *_chara;


	bool onContactBegin(cocos2d::PhysicsContact& contact);


	void setPhysicsWorld(PhysicsWorld* world) {
		mWorld = world;
		mWorld->setGravity(Vect(0, -980));  // No gravity
	}
	PhysicsWorld* getPhysicsWorld();


	PhysicsWorld* mWorld;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void GoToPauseScene();

	void onKeyPresed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void update(float dt);

	void createplatform(double x, double y, double z, double scale, double bodyscalex, double bodyscaley, double xoffste, double yoffset);

	struct Command {
		std::string name;
		std::string help;
		std::function<void(int, const std::string&)> callback;
	};

    // implement the "static create()" method manually
    CREATE_FUNC(Game);

};

#endif // __HELLOWORLD_SCENE_H__