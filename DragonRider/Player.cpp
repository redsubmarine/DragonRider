//
//  Player.cpp
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#include "Player.h"

using namespace cocos2d;


bool Player::init(){
    if (!CCSprite::init()) {
        return false;
    }
    //화면의 가운데 아래쪽에 위치시키자
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    this->setPosition(ccp(winSize.width/2, 50));
    //왼쪽 날개 만든다.
    leftWing = CCSprite::createWithSpriteFrameName("player_wing.png");
    leftWing->setAnchorPoint(ccp(1.0, 1.0));
    leftWing->setPosition(ccp(10, 30));
    this->addChild(leftWing, -1);
    
    //오른쪽 날개 만든다.
    rightWing = CCSprite::createWithSpriteFrameName("player_wing.png");
    rightWing->setAnchorPoint(ccp(0.0, 1.0));
    rightWing->setFlipX(true);
    rightWing->setPosition(ccp(this->boundingBox().size.width-10, 30));
    this->addChild(rightWing, -1);
 
    
    return true;
}

