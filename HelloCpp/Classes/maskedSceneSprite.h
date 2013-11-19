

#ifndef __HelloCpp__maskedSceneSprite__
#define __HelloCpp__maskedSceneSprite__

#include <iostream>
#include "cocos2d.h"
#include "GLProgramWithMyUnifos.h"
using namespace cocos2d;
class CmaskedSceneSprite:public CCSprite
{
public:
    CmaskedSceneSprite(){
        r=180;
        wickR_div_r=0.7;
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        c=CCPoint(winSize.width/2,winSize.height/2);
        maxBrightness=3;
        minBrightness=0.4;
        wickBaseColor[0]=1,wickBaseColor[1]=0.3,wickBaseColor[2]=0.0,wickBaseColor[3]=1;
        wickBrightness=2.0;wickBrightness=MAX(1.0,wickBrightness);
        
    }
    virtual ~CmaskedSceneSprite(){
    
    }
    void draw();
    bool init(CCTexture2D*texture);
    CGLProgramWithMyUnifos program;
    float r;//r of the spot
    CCPoint c;
    float maxBrightness;
    float minBrightness;
    
    float wickR_div_r;//percentage of wick r on spot r (the value is from 0 to 1), namely wirckR=wickR_div_r*r
    float wickBaseColor[4];
    float wickBrightness;
    
    
};
#endif /* defined(__HelloCpp__maskedSceneSprite__) */
