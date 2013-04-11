//
//  HUDLayer.h
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#ifndef __DragonRider__HUDLayer__
#define __DragonRider__HUDLayer__

#include <iostream>
#include "cocos2d.h"

class HUDLayer : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HUDLayer);
    
    //변수와 매서드 선언은 여기에
    
};

#endif /* defined(__DragonRider__HUDLayer__) */
