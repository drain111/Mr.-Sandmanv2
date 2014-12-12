#ifndef __SELECTLEVEL_SCENE_H__
#define __SELECTLEVEL_SCENE_H__

#include "cocos2d.h"
#include "CharacterScene.h"
#include "PlatformScene.h"
#include "CXBOXController.h"
#include "HUD.h"

USING_NS_CC;

class Selectlevel : public cocos2d::Layer
{
	EventKeyboard::KeyCode _pressedKey;
	bool moverderecha;
	bool moverizq;
	bool arriba;
	bool rotar;
	bool free;
	Array *_houses;
	CXBOXController* Player1;
	Camera *camera;
	bool selecciondenivel;
	int selectedtag = 0;
	bool changescene = false;
	Sprite3D *casafinal;
	CCUserDefault *def;
	HUD *hud;

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
	
	void createhouse(int x, int tag);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void update(float dt);

	void GoToGameScene();

	void goToMainMenu();
	void Restart();

	struct Command {
		std::string name;
		std::string help;
		std::function<void(int, const std::string&)> callback;
	};

    // implement the "static create()" method manually
    CREATE_FUNC(Selectlevel);

};

#endif // __HELLOWORLD_SCENE_H__