//
//  GameLayer.h
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#ifndef __DragonRider__GameLayer__
#define __DragonRider__GameLayer__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

NS_CC_BEGIN
class Bullet;
class GameLayer : public CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);
    
    virtual void update(float delta);
    virtual void updateBullet(float deltaTime);
    virtual void onEnter();

    //변수와 매서드 선언은 여기에
    
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
    
    
    void initBackground();

    void initPlayer();
	void initEnemys();
    void initBullets();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	
	
};

NS_CC_END

#endif /* defined(__DragonRider__GameLayer__) */
