#ifndef __LABERINT3_SCENE_H__
#define __LABERINT3_SCENE_H__

USING_NS_CC;

#include "cocos2d.h"
#include "CharacterScene.h"
#include "PlatformScene.h"
#include "CXBOXController.h"
#include "HUD.h"

class LABERINT3 : public cocos2d::Layer
{
private:
	EventKeyboard::KeyCode _pressedKey;
	bool moverderecha;
	bool moverizq;
	bool arriba;
	bool rotar;
	cocos2d::Array *_plataformas;
	Array *_puertas;
	int i;
	int j;
	int k;
	bool free;
	bool selecciondenivel;
	int selectedtag;
	bool changescene;
	Door *puertafinal;
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
	void createdoor(int x, int tag);
	void onKeyPresed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void update(float dt);

	void createplatform(double x, double y, double z, double scale, double bodyscalex, double bodyscaley, double xoffste, double yoffset, std::string name);

	void GotoNext();
	void GotoMenuScene();
	void Restart();

	struct Command {
		std::string name;
		std::string help;
		std::function<void(int, const std::string&)> callback;
	};

    // implement the "static create()" method manually
    CREATE_FUNC(LABERINT3);

};

#endif // __HELLOWORLD_SCENE_H__