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
    

     //다이렉터에서 화면의 크기를 알아온다.
//     CGSize size = [[CCDirector sharedDirector] winSize];
    CCSize size = CCDirector::sharedDirector()->getWinSize();
     //제목으로 만들 레이블을 시스템 폰트를 사용해서 만든다.
//     CCLabelTTF *label = [CCLabelTTF labelWithString:@"Dragon Rider" fontName:@"HelveticaNeue" fontSize:36];
    CCLabelTTF *label = CCLabelTTF::create("Dragon Rider", "HelveticaNeue", 36);
     //레이블의 위치를 지정한다.
//     label.position = ccp( size.width/2, size.height/2 + 100 );
    label->setPosition(ccp(size.width/2, size.height/2 + 100));
     //레이블을 자식으로 추가한다.
//     [self addChild:label];
    this->addChild(label);
    
    
//     CCLabelTTF *label2 = [CCLabelTTF labelWithString:@"Made by @krazyeom" fontName:@"HelveticaNeue" fontSize:30];
    CCLabelTTF *label2 = CCLabelTTF::create("Made by redsubmarine", "HelveticaNeue", 30);
     //레이블의 위치를 지정한다.
//     label2.position = ccp( size.width/2, size.height/2 + 60 );
    label2->setPosition(ccp(size.width/2, size.height/2 +60));
     //레이블을 자식으로 추가한다.
    this->addChild(label2);
//     [self addChild:label2];
    
//     //메뉴 아이템의 폰트를 변경한다.
//     [CCMenuItemFont setFontName:@"AppleSDGothicNeo-Medium"];

     //메뉴 아이템 블럭
//     CCMenuItem *startItem = [CCMenuItemFont itemWithString:@"Start" block:^(id sender)  {
//     //Start 메뉴 버튼이 눌렸을 경우, GameScene을 화면 전환과 함께 호출한다.
//     [[CCDirector sharedDirector] replaceScene:[GameScene node]];
//     }];
    CCMenuItemFont *startItem = CCMenuItemFont::create("Start", this, menu_selector(MenuLayer::goGameScene));
    //메뉴 버튼을 메뉴에 추가한다.
//     CCMenu *menu = [CCMenu menuWithItems:startItem, nil];
    CCMenu *menu = CCMenu::create(startItem, NULL);
     //세로 정렬로 각 메뉴의 사잇값으로 20을 준다.
//     [menu alignItemsVerticallyWithPadding:20];
    menu->alignItemsVerticallyWithPadding(20);
     //메뉴의 위치를 지정한다.
//     [menu setPosition:ccp( size.width/2, size.height/2 - 50)];
    menu->setPosition(ccp(size.width/2, size.height/2 - 50));
     //메뉴를 자식으로 추가한다.
//     [self addChild:menu];
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