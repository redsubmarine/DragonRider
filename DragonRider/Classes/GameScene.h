//
//  GameScene.h
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//
//

#ifndef __DragonRider__GameScene__
#define __DragonRider__GameScene__

#include <iostream>
#include "cocos2d.h"

NS_CC_BEGIN
class HUDLayer;
class GameLayer;

class GameScene : public CCScene
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameScene);
    
    //변수와 매서드 선언은 여기에

    GameLayer *gameLayer;
    HUDLayer *hudLayer;
    
    
    
};

NS_CC_END
#endif /* defined(__DragonRider__GameScene__) */
