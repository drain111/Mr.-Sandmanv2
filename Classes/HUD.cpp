#include "HUD.h"
#include "cocos2d.h"

USING_NS_CC;

HUD::HUD(int vidasJ)
{
	vidas=vidasJ;
	__String *text= __String::createWithFormat("lifes: %d",vidas);
	LabelTTF *puntos = LabelTTF::create(text->getCString(),"Cryptik",12.0f,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
	addChild(puntos);
}


HUD::~HUD(void)
{
}
