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
#include "Bullet.h"
#include "MenuLayer.h"
#include "HUDLayer.h"
#include "Dust.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

bool GameLayer::init(){
    if (!CCLayer::init() ) {
        return false;
    }
    
    //초기화
    winSize = CCDirector::sharedDirector()->getWinSize();
    this->initBackground();
    
    //마지막 총알 번호를 위해 초기화
    lastBullet = 0;
    //총알등을 위해 배치노드 사용
    batchNode = CCSpriteBatchNode::create("dragonRiderSprite.pvr");
    this->addChild(batchNode);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("dragonRiderSprite.plist");
    
    this->initPlayer();
    this->initEnemys();
    this->initBullets();
    score = 0;
    
    
    return true;
}

GameLayer::~GameLayer(){
    CC_SAFE_RELEASE(bulletsArray);
    CC_SAFE_RELEASE(enemysArray);
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
    enemysArray->retain();
    float width = winSize.width/kMaxMonster;
    for (int i=0; i<kMaxMonster; i++) {
        Enemy *enemy = Enemy::create();
        this->addChild(enemy, 98);
        enemy->setPosition(ccp(i*width+width/2, winSize.height +enemy->boundingBox().size.height/2));
        enemysArray->addObject(enemy);
    }
    
}
#define kMaxBullets 30
void GameLayer::initBullets(){
    //총알 갯수만큼 배열을 만든다.
    bulletsArray = CCArray::createWithCapacity(kMaxBullets);
    bulletsArray->retain();
    //총알 갯수만큼 배열에 넣는다.
    for (int i = 0; i < kMaxBullets; i++) {
        //총알 노드 생성
        Bullet *bullet = Bullet::create();
        bullet->setVisible(false);
        bullet->setPosition(ccp(player->getPosition().x, player->getPosition().y+ player->boundingBox().size.height));
        batchNode->addChild(bullet, 99);
        bulletsArray->addObject(bullet);
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
#pragma mark - 여기가 일단 문제
    //플레이어와 캐릭터 충돌을 위해 배열에서 적을 하나 꺼낸다.
    CCObject *object = NULL;
    CCARRAY_FOREACH(enemysArray, object)
    {
        Enemy *enemy = dynamic_cast<Enemy*>(object);
        //적이 이미 죽은 상태이면 그냥 넘어간다.
        if (enemy->state == kDestoryed) {
            continue;
        }
        //총알을 하나 배열에서 꺼낸다
        CCObject *obj;
        CCARRAY_FOREACH(bulletsArray, obj){
            Bullet *bullet = dynamic_cast<Bullet *>(obj);
            //총알이 없어진 상태면 그냥 넘어간다.
            if (!bullet->isVisible()) {
                continue;
            }
            //총알과 적이 충돌나는지 체크
            if (!isCollision && bullet->boundingBox().intersectsRect(enemy->boundingBox())) {
                //총알을 없애고,
                bullet->setVisible(false);
                //미사일로 적을 공격해서 0점을 받아오는지를 체크
                if (!enemy->attackedWithPoint(bullet->bulletType))
				{
                    //총알이 몬스터에 맞을때 싸운드 효과를 재생한다.
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mon_damage.mp3");
                    //미사일로 적을 공격해서 0점을 받아오는지를 체크
                    if (!enemy->attackedWithPoint(bullet->bulletType)){
                        //싸운드 효과를 재생한다.
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mon_die.mp3");
                    }
                    
                    Dust *dust = Dust::create();
                    dust->setPosition(enemy->getPosition());
                    this->addChild(dust);
                    dust->animateDusts();
                }
            }
        }
        //적과 플레이어가 충돌나는지 체크
        if (!isCollision && enemy->boundingBox().intersectsRect(player->boundingBox())) {
            isCollision = true;
            player->setVisible(false);
            //충돌하게되면 총알을 다 없앤다
            this->unschedule(schedule_selector(GameLayer::updateBullet));
            CCObject *object;
            CCARRAY_FOREACH(bulletsArray, object){
                Bullet *bullet = dynamic_cast<Bullet *>(object);
                bullet->setVisible(false);
                bullet->removeFromParentAndCleanup(true);
            }
            
            Dust *dust = Dust::create();
            dust->setPosition(player->getPosition());
            this->addChild(dust, 1000);
            dust->animateExplosions();
            
            
            
            //딜레이를 위한 액션
            CCDelayTime *delay = CCDelayTime::create(2.0f);

            CCCallFunc *allStop = CCCallFunc::create(this, callfunc_selector(GameLayer::allStop));
            
            CCCallFunc *block = CCCallFunc::create(this, callfunc_selector(GameLayer::block));
            
            //액션을 순서대로 준비.
            CCSequence *seq = CCSequence::create(allStop, delay, block, NULL);
            //액션 실행
            this->runAction(seq);
        }
    }
}

void GameLayer::allStop(){
    this->setTouchEnabled(false);
}
void GameLayer::block()
{
    CCDirector::sharedDirector()-> replaceScene(MenuLayer::scene());
}


void GameLayer::updateBullet(float deltaTime){
    //배열에서 하나씩 총알을 꺼낸다.
    Bullet *bullet = (Bullet *) bulletsArray->objectAtIndex(lastBullet);
    //움직일때는 보이게 설정
    bullet->setVisible(true);
    //총알의 위치는 플레이어 캐릭터의 앞에 위치
    bullet->setPosition(ccp(player->getPosition().x, player->getPosition().y + player->boundingBox().size.height/2));
    //마지막 총알이 배열의 마지막이면 다시 초기화
    if (++lastBullet == kMaxBullets) {
        lastBullet = 0;
    }
}

void GameLayer::updateScore(float deltaTime){
    hud->setScoreText(score++);
}

void GameLayer::onEnter()
{
    CCLayer::onEnter();
    //터치 이벤트를 받는다.
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    //배경 움직임과 충돌을 체크할때 사용하는 메인 스케쥴
    this->scheduleUpdate();
    //스케줄을 통해 updateBullet 호출
    this->schedule(schedule_selector(GameLayer::updateBullet), 0.05f);
    //점수를 위한 스케쥴
    this->schedule(schedule_selector(GameLayer::updateScore), 0.01f);
    
    //시작되면 배경 백그라운드 음악 재생
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back.mp3", true);
}


bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //터치가 시작되면 이전 값과 비교를 위해 저장한다. UI좌표계를 cocos 좌표계로 변환
    previousPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
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


