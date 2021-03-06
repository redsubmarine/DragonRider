//
//  GameLayer.h
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#ifndef __DragonRider__GameLayer__
#define __DragonRider__GameLayer__


#include "cocos2d.h"

using namespace cocos2d;

NS_CC_BEGIN
class Bullet;
class HUDLayer;
class GameLayer : public CCLayer
{
    
    //변수
    
    CCSize winSize;
    CCPoint previousPoint;
    
    CCSprite *backgroundImage1;
    CCSprite *backgroundImage2;
    
    CCSprite *player;
    //적을 저장할 array
    CCArray *enemysArray;
    //총알을 담을 array
    CCArray *bulletsArray;
    //마지막 총알 확인용
    int lastBullet;
    //충돌했는지 체크용
    bool isCollision;
    
    CCSpriteBatchNode *batchNode;
    //점수 저장용 변수
    int score;

    
public:
    
    //HUD
    HUDLayer *hud;
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);
    ~GameLayer();
    
    virtual void update(float delta);
    void updateBullet(float deltaTime);
    void updateScore(float deltaTime);
    
    virtual void onEnter();
    //매서드
    
    void initBackground();

    void initPlayer();
	void initEnemys();
    void initBullets();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    //CCCallBlock 대용
	void allStop(); //터치이벤트를 더이상 받지 않는다.
    void block();   //메뉴 레이어로 돌아간다.
	
};

NS_CC_END

#endif /* defined(__DragonRider__GameLayer__) */
