//
//  Enemy.h
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#ifndef __DragonRider__Enemy__
#define __DragonRider__Enemy__

#include "cocos2d.h"
//두종류의 적
typedef enum {
    kRed = 0,
    kWhite
} EnemyType;

//적의 상태를 나타내기 위해
typedef enum {
    kDestoryed = 0,
    kNormal = 1
} State;
NS_CC_BEGIN
class EnergyGauge;
class Enemy : public::cocos2d::CCSprite {
    
    virtual bool init();
    virtual void update(float delta);
    virtual void onEnter();
public:
    CREATE_FUNC(Enemy);
    //변수
    bool wingDown;
    //적의 종류 : 약한놈과 강한놈으로 두 가지로만 구분
    EnemyType enemyType;
    //현재 상태 값 : 죽었는지, 살았는지로 구분
    State state;
    int energy;
    CCSprite *leftWing;
    CCSprite *rightWing;
    CCSprite *leftEye;
    CCSprite *rightEye;
    
    EnergyGauge *gauge;
    
    //매서드
    void reset();
    int attackedWithPoint(int point);
    void destroy();
};

NS_CC_END
#endif /* defined(__DragonRider__Enemy__) */


