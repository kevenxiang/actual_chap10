//
//  ParticleEffectTest.hpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#ifndef ParticleEffectTest_hpp
#define ParticleEffectTest_hpp

#include <stdio.h>
#include "cocos2d.h"

class ParticleEffectTest : public cocos2d::Layer {
public:
    
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(ParticleEffectTest);
};

#endif /* ParticleEffectTest_hpp */
