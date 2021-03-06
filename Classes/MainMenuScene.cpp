#include "MainMenuScene.h"
#include "Selectlevelscene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Laberint3Scene.h"

USING_NS_CC;
Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//importar y reproducir musicas
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("musica menu.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("musica menu.mp3",true);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto Start = MenuItemImage::create("mainmenu/start.png", "mainmenu/start(click).png", CC_CALLBACK_1(MainMenu::GoToGameScene,this));

	auto Load = MenuItemImage::create("mainmenu/load.png", "mainmenu/load(click).png", CC_CALLBACK_1(MainMenu::LoadGameScene,this));
	
	auto Exit = MenuItemImage::create("mainmenu/exit.png", "mainmenu/exit(click).png", CC_CALLBACK_1(MainMenu::ExitGame,this));
	
	auto menu = Menu::create(Start, Load, Exit, NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 8);
    this->addChild(menu, 1);

	auto bg = Sprite::create("mainmenu/bg.png");

	bg->setPosition(Point((visibleSize.width/2), (visibleSize.height/2)));

	this->addChild(bg, 0);
    
    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void MainMenu::GoToGameScene(Ref* pSender) 
{
	CCUserDefault *def = CCUserDefault::sharedUserDefault();

	def->setIntegerForKey("vidas", 3);
	def->setIntegerForKey("puntuacion1", 0);
	def->setIntegerForKey("puntuacion2", 0);
	def->setIntegerForKey("puntuacion3", 0);

	def->flush();
	auto scene = Selectlevel::createScene();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);//parar la musica del menu al pasar al juego
   Director::getInstance()->replaceScene(TransitionFade::create(1.0,scene));
}
void MainMenu::ExitGame(Ref* pSender)
{
	exit(0);
}
void MainMenu::LoadGameScene(Ref* pSender)
{
	
	auto scene = Selectlevel::createScene();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);//parar la musica del menu al pasar al juego
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}