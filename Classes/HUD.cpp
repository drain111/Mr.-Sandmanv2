#include "HUD.h"
#include "cocos2d.h"

USING_NS_CC;

HUD::HUD(int vidasJ, bool tiempobool, int tiempolvl)
{
	tiempo=tiempolvl;
	vidas=vidasJ;
	__String *text= __String::createWithFormat("lifes: %d",vidas);
	LabelTTF *puntos = LabelTTF::create(text->getCString(),"Cryptik",24.0f,Size::ZERO,TextHAlignment::RIGHT,TextVAlignment::TOP);
	puntos->setPosition(0, 250);
	addChild(puntos);
	if (tiempobool == true){
		activartiempo();
	}

}


void HUD::activartiempo() {
	frames = 0;
	__String *time = __String::createWithFormat("time: %d ", tiempo);
	timeTTF = LabelTTF::create(time->getCString(), "Cryptik", 24.0f, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::TOP);
	timeTTF->setPosition(-600, 250);
	addChild(timeTTF);

}
void HUD::update()
{
	frames++;
	if (frames == 60) {
		tiempo--;
		frames = 0;
		__String *time = __String::createWithFormat("time: %d ", tiempo);
		timeTTF->setString(time->getCString());
	}
}
HUD::~HUD(void)
{
	this->cleanup();
}
