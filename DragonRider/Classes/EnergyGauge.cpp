//
//  EnergyGauge.cpp
//  DragonRider
//
//  Created by 양원석 on 4/13/13.
//
//

#include "EnergyGauge.h"

using namespace cocos2d;


bool EnergyGauge::init(){
    if (!CCNode::init()) {
        
        return false;
    }
    
    return true;
}

EnergyGauge* EnergyGauge::energyGaugeWithMaxSize(CCSize size, CCFloat _maxValue){
    EnergyGauge *energyGauge = new EnergyGauge;
    if (energyGauge && energyGauge->initWithMaxSize(size, _maxValue)) {
        energyGauge->autorelease();
        return energyGauge;
    }
    CC_SAFE_DELETE(energyGauge);
    return NULL;
}
bool EnergyGauge::initWithMaxSize(CCSize size, CCFloat _maxValue){
    if (!CCNode::init()) {
        return false;
    }
    maxSize = size;
    currentValue = maxValue = _maxValue;
    return true;
}
void EnergyGauge::updateBar(CCFloat currentValue){
    
}
