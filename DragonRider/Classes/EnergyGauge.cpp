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

void EnergyGauge::updateBar(CCFloat _currentValue){
    currentValue = _currentValue;
    if (currentValue.getValue()<0) {
        currentValue = 0;
    }else if (currentValue.getValue()> maxValue.getValue()){
        currentValue = maxValue;
    }
}

void EnergyGauge::draw(){
    //최대값기준으로 %로 환산한 너비값
    CCFloat width = (currentValue.getValue() / maxValue.getValue())* (float)maxSize.width;
    //라인의 두께는 높이
    glLineWidth(maxSize.height);
    //100% 일때는 Green
    if (currentValue.getValue() == maxValue.getValue()) {
        ccDrawColor4B(255, 255, 0, 255);
    }
    //그외에는 Red
    else
        ccDrawColor4B(255, 0, 0, 255);
    ccDrawLine(ccp(0,0), ccp(width.getValue(), 0));
//    ccDrawLine(ccp(0, 0), ccp(width, 0));
}

