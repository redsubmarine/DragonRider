//
//  Dust.h
//  DragonRider
//
//  Created by 양원석 on 4/14/13.
//
//

#ifndef __DragonRider__Dust__
#define __DragonRider__Dust__

#include "cocos2d.h"
using namespace cocos2d;
NS_CC_BEGIN

class Dust: public::cocos2d::CCSprite {
    CCArray *dusts;
    CCArray *explosions;
    CCSpriteBatchNode *batch;
    
    virtual bool init();
    virtual ~Dust();
    //CCCallBlock를 쓸수 없으므로 함수를 선언
    void block(CCSprite *explosion);
    void block2(CCSprite *dust);

public:
    CREATE_FUNC(Dust);
    
    void animateDusts();
    void animateExplosions();
};


NS_CC_END

#endif /* defined(__DragonRider__Dust__) */
