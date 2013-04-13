//
//  HUDLayer.h
//  DragonRider
//
//  Created by 양원석 on 4/14/13.
//
//

#ifndef __DragonRider__HUDLayer__
#define __DragonRider__HUDLayer__

#include "cocos2d.h"
NS_CC_BEGIN

class HUDLayer: public::cocos2d::CCLayer {
    
    virtual bool init();
    CCLabelTTF *scoreLabel;

public:
    
    CREATE_FUNC(HUDLayer);
    void setScoreText(int score);
    
};


NS_CC_END
#endif /* defined(__DragonRider__HUDLayer__) */
