#ifndef __GAME2_SCENE_H__
#define __GAME2_SCENE_H__

USING_NS_CC;


#include "cocos2d.h"
#include "CharacterScene.h"
#include "PlatformScene.h"
#include "CXBOXController.h"
#include "HUD.h"

class Game2 : public cocos2d::Layer
{
	EventKeyboard::KeyCode _pressedKey;
	bool moverderecha;
	bool moverizq;
	bool arriba;
	bool rotar;
	cocos2d::Array *_plataformas;
	cocos2d::Array *_trampas;
	int i;
	int j;
	int k;
	bool free;
	CXBOXController* Player1;
	Camera *camera;
	LabelTTF *lifes;
	bool abrir;
	Sprite3D *esfera;
	int puntuacion;
	HUD *hud;
	CCUserDefault *def;
public:
	
	Character *_chara;


	bool onContactBegin(cocos2d::PhysicsContact& contact);

	

	void setPhysicsWorld(PhysicsWorld* world) {
		mWorld = world;
		mWorld->setGravity(Vect(0, -980));  // No gravity
	}
	PhysicsWorld* getPhysicsWorld();
	bool muerto;

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

	void createtrap(double x, double y, double z, std::string name);

	void createplatform(double x, double y, double z, double scale, double bodyscalex, double bodyscaley, double xoffste, double yoffset, std::string name);

	void GotoMenuScene();

	void Restart();

	struct Command {
		std::string name;
		std::string help;
		std::function<void(int, const std::string&)> callback;
	};

    // implement the "static create()" method manually
    CREATE_FUNC(Game2);

};

#endif // __HELLOWORLD_SCENE_H__