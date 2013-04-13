//
//  HUDLayer.cpp
//  DragonRider
//
//  Created by 양원석 on 4/14/13.
//
//

#include "HUDLayer.h"

using namespace cocos2d;

bool HUDLayer::init(){
    if (!CCLayer::init()) {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    scoreLabel = CCLabelTTF::create("0M", "Thonburi", 40);
    scoreLabel->setColor(ccc3(255, 0, 0));
    scoreLabel->setPosition(ccp(560, winSize.height-100));
    this->addChild(scoreLabel);
    
    return true;
}

void HUDLayer::setScoreText(int score){
    CCString *scoreString = CCString::createWithFormat("%dM", score);
    scoreLabel->setString(scoreString->getCString());
}