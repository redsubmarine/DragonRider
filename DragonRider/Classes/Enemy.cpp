//
//  Enemy.cpp
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#include "Enemy.h"

using namespace cocos2d;

bool Enemy::init(){
    if (!CCSprite::initWithSpriteFrameName("dragon_01_body.png")) {
        return false;
    }
    state = kNormal;
    //적의 기본 에너지는 100
    energy = 100;
    wingDown = false;
    
    //왼쪽날개 스프라이트
    leftWing = CCSprite::createWithSpriteFrameName("dragon_01_wing.png");
    leftWing->setAnchorPoint(ccp(1.0, 0));
    leftWing->setPosition(ccp(10, this->boundingBox().size.height/2));
    this->addChild(leftWing);
    
    //오른쪽날개 스프라이트
    rightWing = CCSprite::createWithSpriteFrameName("dragon_01_wing.png");
    rightWing->setFlipX(true);
    rightWing->setAnchorPoint(ccp(0.0, 0));
    rightWing->setPosition(ccp(this->boundingBox().size.width-10, this->boundingBox().size.height/2));


    this->addChild(rightWing);
    
    //왼쪽눈 스프라이트
    leftEye = CCSprite::createWithSpriteFrameName("dragon_eye_1.png");
    leftEye->setPosition(ccp(20,60));
    this->addChild(leftEye);
    //오른쪽눈 스프라이트
    rightEye = CCSprite::createWithSpriteFrameName("dragon_eye_1.png");
    rightEye->setPosition(ccp(60,60));
    this->addChild(rightEye);
    
    
    
    return true;
}

#define kMaxEnemyType 2

void Enemy::update(float delta){
    //적의 움직임 가속도 값
    CCPoint enemyScrollVel = ccp(0, -250);
    //현재 적의 위치 값
    CCPoint enemyPos = this->getPosition();
    //화면 아래로 벗어나는지 체크
    if (enemyPos.y + this->boundingBox().size.height / 2 <= 0) {
        //벗어나면 리셋 한다.
        this->reset();
        //아닐 경우
    } else{
        //움직이게 위치값을 아래로 이동
        enemyPos = ccpAdd(ccpMult(enemyScrollVel, delta), enemyPos);
        //위치 시킨다.
        this->setPosition(enemyPos);
    }
}

void Enemy::reset(){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //적의 위치를 화면 상단으로 부터 시작한다.
    this->setVisible(true);
    state = kNormal;
    this->setPosition(ccp( this->getPosition().x, winSize.height + this->boundingBox().size.height / 2 - 1 ));
	this->setVisible(true);
	
    state = kNormal;
    //적의 이미지를 바꿔주기 위해 랜덤 값 생성
    int random = ( (float)arc4random() / (float)0xffffffff ) * kMaxEnemyType;
    
    switch (random) {
        case kWhite:
            //에너지를 100으로 할당
            energy = 100;
            //적의 타입설정
            enemyType = kWhite;
            //이미지 변경을위해 프레임에 파일이름으로 스프라이트 프레임 케쉬로 부터 찾아서 할당
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("dragon_01_body.png"));
            leftWing->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("dragon_01_wing.png"));
            rightWing->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("dragon_01_wing.png"));
            rightWing->setFlipX(true);
            break;
        case kRed:
            //에너지를 200으로 할당
            energy = 200;
            //적의 타입설정
            enemyType = kRed;
            //프레임에 파일이름으로 스프라이트 프레임 케쉬로 부터 찾아서 할당
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("dragon_02_body.png"));
            leftWing->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("dragon_02_wing.png"));
            rightWing->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("dragon_02_wing.png"));
            rightWing->setFlipX(true);
            break;
        default:
            break;
    }
}

void Enemy::onEnter(){
    CCSprite::onEnter();
    this->scheduleUpdate();
}

int Enemy::attackedWithPoint(int point){
    //공격받은 숫자만큼 에너지를 줄인다.
    energy -= point;
    //0 미만이 되면 0을, 아니면 현재 에너지를 반환
    if (energy<=0) {
        //죽으면 숨긴다
        this->destroy();
    }
    return energy;
}

void Enemy::destroy(){
    //죽으면 상태값을 변경
    state = kDestoryed;
    //에너지는 0
    energy = 0;
    //그리고 숨긴다.
    this->setVisible(false);
}