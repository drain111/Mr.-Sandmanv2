#pragma once
#include "cocos2d.h"

class HUD : public cocos2d::Layer
{
	
public:
	int vidas;
	HUD(int vidas);
	~HUD(void);
};

