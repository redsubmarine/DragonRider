//
//  Bullet.cpp
//  DragonRider
//
//  Created by 양원석 on 4/12/13.
//
//

#include "Bullet.h"

using namespace cocos2d;

bool Bullet::init(){
    if (!CCSprite::initWithSpriteFrameName("bullet_01_01.png")) {
        return false;
    }
    
    bulletType = kFirst;
    
    return true;
}

void Bullet::updateBullet(float deltaTime){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //총알의 움직임 가속도
    CCPoint bulletVel = ccp(0, 600);
    //총알의 현재위치
    CCPoint currentPosition = this->getPosition();
    //화면밖으로 나가면 총알을 숨긴다
    if (currentPosition.y > winSize.height) {
        this->setVisible(false);
    }else{
        //아니면 계속해서 앞으로 보낸다.
        this->setPosition(ccpAdd(ccpMult(bulletVel, deltaTime), this->getPosition()));
    }
}

void Bullet::onEnter(){
    CCSprite::onEnter();
    //schedule로 호출
    this->schedule(schedule_selector(Bullet::updateBullet), 0.05);
}