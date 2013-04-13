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
    if (!CCSprite::initWithSpriteFrameName("player.png")) {
        return false;
    }
    //화면의 가운데 아래쪽에 위치시키자
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    this->setPosition(ccp(winSize.width/2, 100));
    //왼쪽 날개 만든다.
    leftWing = CCSprite::createWithSpriteFrameName("player_wing.png");
    leftWing->setAnchorPoint(ccp(1.0, 1.0));
    leftWing->setPosition(ccp(10, 60));
    this->addChild(leftWing, -1);
    
    //오른쪽 날개 만든다.
    rightWing = CCSprite::createWithSpriteFrameName("player_wing.png");
    rightWing->setAnchorPoint(ccp(0.0, 1.0));
    rightWing->setFlipX(true);
    rightWing->setPosition(ccp(this->boundingBox().size.width-10, 60));
    this->addChild(rightWing, -1);
 
    
    return true;
}

void Player::updateWings(float deltaTime){
    //왼쪽 날개 애니메이션을 위한 날개 내렸다 올리기
    CCRotateTo *leftWingDown = CCRotateTo::create(0.2, -30, 60);
    CCRotateTo *leftWingUp = CCRotateTo::create(0.2, 0, 0);
    //오른쪽 날개 애니메이션을 위한 날개 내렸다 올리기
    CCRotateTo *rightWingDown = CCRotateTo::create(0.2, 30, -60);
    CCRotateTo *rightWingUp = CCRotateTo::create(0.2, 0, 0);
    
    //번갈아 가면서 날개짓을 한다.
    if ((wingDown = !wingDown)) {
        leftWing->runAction(leftWingDown);
        rightWing->runAction(rightWingDown);
    }else{
        leftWing->runAction(leftWingUp);
        rightWing->runAction(rightWingUp);
    }
}

void Player::onEnter(){
    CCSprite::onEnter();
    this->schedule(schedule_selector(Player::updateWings), 0.2);
}









