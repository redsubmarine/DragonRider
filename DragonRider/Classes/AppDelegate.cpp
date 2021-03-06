//
//  DragonRiderAppDelegate.cpp
//  DragonRider
//
//  Created by 양원석 on 4/11/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MenuLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // 배경음악을 위한 음악
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("back.mp3");
    // 적이 죽을 경우을 위한 사운드 효과
    SimpleAudioEngine::sharedEngine()->preloadEffect("mon_die.mp3");
    // 적이 피해를 입었을 경우을 위한 사운드 효과
    SimpleAudioEngine::sharedEngine()->preloadEffect("mon_damage.mp3");
        
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());


    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
#if TARGET_IPHONE_SIMULATOR
    pDirector->setAnimationInterval(1.0 / 30);
#else
    pDirector->setAnimationInterval(1.0 / 60);
#endif
    

    // create a scene. it's an autorelease object
    CCScene *pScene = MenuLayer::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
