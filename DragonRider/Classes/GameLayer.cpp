//
//  GameLayer.cpp
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#include "GameLayer.h"
#include "Player.h"

using namespace cocos2d;

bool GameLayer::init(){
    if (!CCLayer::init() ) {
        return false;
    }
    
    //초기화
    winSize = CCDirector::sharedDirector()->getWinSize();
    this->initBackground();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("dragonRiderSprite.plist");
    
    this->initPlayer();
    
    return true;
}

void GameLayer::initBackground(){
    backgroundImage1 = CCSprite::create("01.png");
    backgroundImage1->setAnchorPoint(CCPointZero);
    this->addChild(backgroundImage1, -1);
    
    backgroundImage2 = CCSprite::create("01.png");
    backgroundImage2->setAnchorPoint(CCPointZero);

    backgroundImage2->setPosition(ccp(0, backgroundImage2->boundingBox().size.height));
    this->addChild(backgroundImage2, -1);
    
}

void GameLayer::initPlayer(){
    //플레이어 케릭터를 생성한다.
    player = Player::create();

    //가장 위에 위치 시킨다.
    this->addChild(player, 99);

}


void GameLayer::update(float delta){

     // 배경화면 움직이는 속도, 현재 위치에 이동할 위치를 ccpAdd로 더하는 방식
    CCPoint backgroundScrollVel = ccp(0, -100);
    
     // 현재 이미지1의 위치 값을 불러온다.
    CCPoint currentPos = backgroundImage1->getPosition();
    
     // 1번 이미지가 스크롤 되서 사라지고, 2번 이지미가 1번 이미지의 초기 위치에 오면 최초위치로 이동
    if (currentPos.y < - winSize.height) {
        backgroundImage1->setPosition(CCPointZero);
        currentPos = ccp(0, backgroundImage2->boundingBox().size.height);
        backgroundImage2->setPosition(currentPos);
    }else{
        backgroundImage1->setPosition(ccpAdd(ccpMult(backgroundScrollVel, delta), backgroundImage1->getPosition()));
        backgroundImage2->setPosition(ccpAdd(ccpMult(backgroundScrollVel, delta), backgroundImage2->getPosition()));
    }
}

void GameLayer::onEnter(){
    CCLayer::onEnter();
    this->scheduleUpdate();
}









