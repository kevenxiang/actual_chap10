//
//  MyParticle.hpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#ifndef MyParticle_hpp
#define MyParticle_hpp

#include <stdio.h>
#include "cocos2d.h"

class MyParticle : public cocos2d::ParticleSystemQuad {
public:
    // create函数
    static MyParticle *create();
    // 初始化粒子函数
    virtual bool initWithTotalParticles(int numberOfParticles);
};

#endif /* MyParticle_hpp */
