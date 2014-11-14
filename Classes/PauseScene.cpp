#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PauseScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

	

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto ResumeItem = MenuItemImage::create("pausa/resume.png",
                                          "pausa/resume(Click).png",
                                          CC_CALLBACK_1(PauseScene::resumeGameScene, this));

	auto RetryItem = MenuItemImage::create("pausa/restart.png",
                                          "pausa/restart(Click).png",
                                          CC_CALLBACK_1(PauseScene::retryGameScene, this));

	auto MenuItem = MenuItemImage::create("pausa/mainmenu.png",
										  "pausa/mainmenu(Click).png",
										  CC_CALLBACK_1(PauseScene::goToMainMenu, this));

	auto menu = Menu::create (ResumeItem,RetryItem,MenuItem,  NULL);
    
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 16);
    this->addChild(menu, 1);


	auto background = Sprite::create("mainmenu/bg.png");
 
	background->setPosition(Point((visibleSize.width /2),
	(visibleSize.height /2)));
 
	addChild(background, 0);



    return true;
}

void PauseScene::resumeGameScene(Ref *pSender) {
 Director::getInstance()->popScene();
}
void PauseScene::goToMainMenu(Ref *pSender) {
 auto scene = MainMenu::createScene();
 
 Director::getInstance()->popScene();
 Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0,scene,0));
}
void PauseScene::retryGameScene(Ref *pSender) {
 auto scene = Game::createScene();
 
 Director::getInstance()->popScene();
 Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0,scene));

}