//
//  MyParticleScene.hpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#ifndef MyParticleScene_hpp
#define MyParticleScene_hpp

#include <stdio.h>
#include "cocos2d.h"

class MyParticleScene : cocos2d::Layer {
public:
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MyParticleScene);
};

#endif /* MyParticleScene_hpp */
