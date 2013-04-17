//
//  MenuLayer.cpp
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#include "MenuLayer.h"
#include "GameScene.h"
using namespace cocos2d;

bool MenuLayer::init(){
    if (!CCLayer::init() ) {
        return false;
    }
    //초기화
    
    //디렉터에서 화면의 크기를 알아온다.
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    //제목으로 만들 레이블을 시스템 폰트를 사용해서 만든다.
    CCLabelTTF *label = CCLabelTTF::create("Dragon Rider", "HelveticaNeue", 36);
    //레이블의 위치를 지정한다.
    label->setPosition(ccp(size.width/2, size.height/2 + 100));
    //레이블을 자식으로 추가한다.
    this->addChild(label);
    
    CCLabelTTF *label1 = CCLabelTTF::create("Made by @krazyeom", "HelveticaNeue", 30);
    //레이블의 위치를 지정한다.
    label1->setPosition(ccp(size.width/2, size.height/2 +30));
    //레이블을 자식으로 추가한다.
    this->addChild(label1);
    
    CCLabelTTF *label2 = CCLabelTTF::create("Revised by @redsubmarine11", "HelveticaNeue", 25);
    //레이블의 위치를 지정한다.
    label2->setPosition(ccp(size.width/2, 100));
    //레이블을 자식으로 추가한다.
    this->addChild(label2);
    
    

    
    
    
    //메뉴 아이템 블럭
    CCMenuItemFont *startItem = CCMenuItemFont::create("Start", this, menu_selector(MenuLayer::goGameScene));
    //메뉴 버튼을 메뉴에 추가한다.
    CCMenu *menu = CCMenu::create(startItem, NULL);

    //세로 정렬로 각 메뉴의 사잇값으로 20을 준다.
    menu->alignItemsVerticallyWithPadding(20);
    //메뉴의 위치를 지정한다.
    menu->setPosition(ccp(size.width/2, size.height/2 - 50));
    
    //메뉴를 자식으로 추가한다.
    this->addChild(menu);
    
    
    return true;
}

void MenuLayer::goGameScene(){
    CCDirector::sharedDirector()->replaceScene(GameScene::create());
}

CCScene * MenuLayer::scene(){
    
    CCScene *scene = CCScene::create();
    MenuLayer *layer = MenuLayer::create();
    scene->addChild(layer);
    
    return scene;
}