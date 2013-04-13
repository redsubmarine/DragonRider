//
//  Player.h
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#ifndef __DragonRider__Player__
#define __DragonRider__Player__

#include "cocos2d.h"

class Player : public::cocos2d::CCSprite {

    virtual bool init();
    virtual void onEnter();
    
    
public:
    CREATE_FUNC(Player);
    
    //변수
    CCSprite *leftWing;
    CCSprite *rightWing;
    
    bool wingDown;
    
    void updateWings(float deltaTime);
};

#endif /* defined(__DragonRider__Player__) */
