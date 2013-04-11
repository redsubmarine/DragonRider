//
//  GameLayer.cpp
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#include "GameLayer.h"
#include "Player.h"
#include "Enemy.h"
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
    this->initEnemys();
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

#define kMaxMonster 5 //기본 적의 수는 5마리

void GameLayer::initEnemys(){
    //적을 저장할 배열을 생성한다.
    enemysArray = CCArray::createWithCapacity(kMaxMonster);
    float width = winSize.width/kMaxMonster;
    for (int i=0; i<kMaxMonster; i++) {
        Enemy *enemy = Enemy::create();
        this->addChild(enemy, 98);
        enemy->setPosition(ccp(i*width+width/2, winSize.height +enemy->boundingBox().size.height/2));
        enemysArray->addObject(enemy);
    }

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

void GameLayer::onEnter()
{
    CCLayer::onEnter();
    //터치 이벤트를 받는다.
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    //배경 움직임과 충돌을 체크할때 사용하는 메인 스케쥴
    this->scheduleUpdate();
}



bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //터치가 시작되면 이전 값과 비교를 위해 저장한다. UI좌표계를 cocos 좌표계로 변환
    previousPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
//    previousPoint = [[CCDirector sharedDirector] convertToGL:[touch locationInView:[touch view]]];
	return true;
}
void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    //이전 값과 비교를 위한 움직였을때 위치 값. UI좌표계를 cocos 좌표계로 변환
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    //플레이어 케릭터의 위치를 ( 기존 위치 X축 값 - 움직인 거리 ), Y축 값은 동일
    player->setPosition(ccp(player->getPosition().x- (previousPoint.x-location.x)*2,
                            player->getPosition().y));

    //왼쪽이나 오른쪽으로 벗어나면 넘어가지 않도록 고정 시킨다.
    if (player->getPosition().x<0) {
        player->setPosition(ccp(0, player->getPosition().y));
    }else if (player->getPosition().x>winSize.width){
        player->setPosition(ccp(winSize.width, player->getPosition().y));
    }
    //현재 위치를 이전 값으로 저장한다.
    previousPoint = location;
}
void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}
void GameLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("ccTouchCancelled");
}



