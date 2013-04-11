//
//  GameScene.cpp
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#include "GameScene.h"
#include "HUDLayer.h"
#include "GameLayer.h"

using namespace cocos2d;

bool GameScene::init(){
    if (!CCNode::init() ) {
        return false;
    }
    
    //초기화
    hudLayer = HUDLayer::create();
    this-> addChild(hudLayer, 1);
    
    gameLayer = GameLayer::create();
    this-> addChild(gameLayer, 0);
    
    /*
     _hudLayer = [HUDLayer node];
     [self addChild:_hudLayer z:1];
     //Game 레이어 추가하기
     _gameLayer = [GameLayer node];
     [self addChild:_gameLayer z:0];
     }
     */
    
    
    return true;
}

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}