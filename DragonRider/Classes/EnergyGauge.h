//
//  EnergyGauge.h
//  DragonRider
//
//  Created by 양원석 on 4/13/13.
//
//

#ifndef __DragonRider__EnergyGauge__
#define __DragonRider__EnergyGauge__

#include "cocos2d.h"

NS_CC_BEGIN

class EnergyGauge : public::cocos2d::CCNode {
    
    virtual bool init();
    
public:
    CREATE_FUNC(EnergyGauge);
    //변수
    CCFloat maxValue = 0.0;
    CCFloat currentValue = 0.0;
    CCSize maxSize;
    //매서드

    static EnergyGauge* energyGaugeWithMaxSize(CCSize size, CCFloat _maxValue);
    bool initWithMaxSize(CCSize size, CCFloat _maxValue);
    void updateBar(CCFloat currentValue);
};


NS_CC_END

#endif /* defined(__DragonRider__EnergyGauge__ ) */
