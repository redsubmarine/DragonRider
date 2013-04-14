//
//  Dust.cpp
//  DragonRider
//
//  Created by 양원석 on 4/14/13.
//
//

#include "Dust.h"

using namespace cocos2d;


#define kMaxDust 10
bool Dust::init(){
    if (!CCSprite::init()) {
        return false;
    }
    
    this->setAnchorPoint(CCPointZero);
    //동일한 이미지의 반복 사용의 효율성을 위해서 배치노드 생성
    batch = CCSpriteBatchNode::create("dragonRiderSprite.pvr");
    this->addChild(batch);
    
    //10개의 먼지 이미지를 사용할 배열생성
    dusts = CCArray::createWithCapacity(kMaxDust);
    dusts->retain();

    for (int i = 0; i<kMaxDust; i++) {
        //먼지 이미지를 스프라이트 시트에서 가져온다.
        CCSprite *dust = CCSprite::createWithSpriteFrameName("dust.png");
        //애니메이션 될 때 보여주기 위해 처음에는 숨긴다
        dust->setVisible(false);
        //작은것에서 커지는 애니메이션을 위해 1/10 으로 작게 만든다.
        dust->setScale(1.0/10.0);
        //배치 노드에 자식노드로 추가
        batch->addChild(dust);
        //배열에 먼지를 추가
        dusts->addObject(dust);
    }
    
    //플레이어 캐릭터가 폭발될 때의 스프라이트를 위한 배열
    explosions = CCArray::createWithCapacity(kMaxDust);
    explosions->retain();
    
    //오른쪽 폭발 효과 스프라이트
    CCSprite *rightDamage = CCSprite::createWithSpriteFrameName("damage.png");
    //폭발시에만 보이게 숨김처리
    rightDamage->setVisible(false);
    //터지는효과를 위해 처음엔 작게 설정
    rightDamage->setScale(0.5);
    rightDamage->setAnchorPoint(CCPointZero);
    this->addChild(rightDamage);
    explosions->addObject(rightDamage);
    
    //왼쪽폭발 효과 스프라이트
    CCSprite *leftDamage = CCSprite::createWithSpriteFrameName("damage.png");
    //폭발시에만 보이게 숨김처리
    leftDamage->setVisible(false);
    //터지는효과를 위해 처음엔 작게 설정
    leftDamage->setScale(0.5);
    //동일한 이미지를 왼쪽에 사용하기위해 X,Y 축 뒤집기(플립)처리
    leftDamage->setFlipX(true);
    leftDamage->setFlipY(true);
    leftDamage->setAnchorPoint(ccp(1.0, 1.0));
    this->addChild(leftDamage);
    explosions->addObject(leftDamage);
    
    //가운데 처지는 스프라이트
    CCSprite *explosion = CCSprite::createWithSpriteFrameName("explosion_01.png");
    //폭발시에만 보이게 숨김처리
    explosion->setVisible(false);
    //터지는효과를 위해 처음엔 작게 설정
    explosion->setScale(0.5);
    this->addChild(explosion);
    explosions->addObject(explosion);
    
    return true;
}

Dust::~Dust(){
    CC_SAFE_RELEASE(dusts);
    CC_SAFE_RELEASE(explosions);
}

void Dust::animateExplosions(){
    CCObject *object;
    CCARRAY_FOREACH(explosions, object){
        CCSprite *explosion = dynamic_cast<CCSprite *>(object);
        
        //보이게 설정한다
        explosion->setVisible(true);
        
        //0.4초동안 3배 커지게 설정
        CCScaleTo *scale = CCScaleTo::create(0.4, 3);
        
        //CCCallBlock를 사용할수 없어서 변조함..
        CCCallFuncO *block = CCCallFuncO::create(this, callfuncO_selector(Dust::block), explosion);
        /*block이라 명명했지만 당연히 block은 아니다*/
        CCSequence *seq = CCSequence::create(scale, block, NULL);
        this->runAction(seq);
    }
}

void Dust::block(CCSprite *explosion){
    
    explosion->setVisible(false);
    this->removeFromParentAndCleanup(true);
}

void Dust::animateDusts(){
    //애니메이션을 위해서 먼지를 세팅
    CCObject *object;
    CCARRAY_FOREACH(dusts, object) {
        CCSprite *dust = dynamic_cast<CCSprite *>(object);
        //숨긴 이미지를 다시 보이게 함
        dust->setVisible(true);
        //10개의 이미지의 크기를 랜덤으로 가져옴
        float scaleRandom = 0.1 + ( (double)arc4random() / (double)0xffffffff);
        //0.3초 동안 크기 변경 애니메이션
        CCScaleTo *scale = CCScaleTo::create(0.3, scaleRandom);
        
        //터지는 x위치를 위해서 랜덤값 1 또는 -1
        int x = ( (double)arc4random()/ (double)0xffffffff)<0.5?-1:1;
        float xRandom = 5 +4*( ((double)arc4random()/ (double) 0xffffffff) *10 *x);
        //터지는 y위치를 위해서 랜덤값 1 또는 -1
        int y = ( (double)arc4random()/ (double)0xffffffff)<0.5?-1:1;
        float yRandom = -30 +4*( ((double)arc4random()/ (double) 0xffffffff) *10 *y);
        

        //0.3초 시간동안 위치 변경 애니메이션
        CCMoveTo *move = CCMoveTo::create(0.3, ccp(xRandom, yRandom));
        //애니메이션이 끝나면 숨기고 자신은 삭제를 위한 CallBack함수
        CCCallFuncO *block = CCCallFuncO::create(this, callfuncO_selector(Dust::block2), dust);
        /*block이라 명명했지만 당연히 block은 아니다*/
        CCSequence *seq = CCSequence::create(move, block, NULL);
        dust->runAction(scale);
        dust->runAction(seq);

        
    }
}

void Dust::block2(CCSprite *dust){
    dust->setVisible(false);
    this->removeFromParentAndCleanup(true);
}

