#pragma once
#include "cocos2d.h"
USING_NS_CC;

class HUD : public cocos2d::Layer
{
	
public:
	int vidas;
	int tiempo;
	int frames;
	LabelTTF *timeTTF;
	HUD(int vidas, bool tiempobool,int tiempolvl);
	void activartiempo();
	void update();
	~HUD(void);
};

