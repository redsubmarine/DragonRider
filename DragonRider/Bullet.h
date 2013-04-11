//
//  Bullet.h
//  DragonRider
//
//  Created by 양원석 on 4/12/13.
//
//

#ifndef __DragonRider__Bullet__
#define __DragonRider__Bullet__

#include "cocos2d.h"

NS_CC_BEGIN

//총알의 종류와 강도
typedef enum{
    //총알의 강도를 나타낸다.
    kFirst = 20
} BulletType;

class Bullet : public::cocos2d::CCSprite {
    
    virtual bool init();
//    virtual void update(float delta);
    virtual void onEnter();
public:
    CREATE_FUNC(Bullet);
    //변수
    BulletType bulletType;
    //매서드
    
    void updateBullet(float deltaTime);

};

NS_CC_END

#endif /* defined(__DragonRider__Bullet__) */
