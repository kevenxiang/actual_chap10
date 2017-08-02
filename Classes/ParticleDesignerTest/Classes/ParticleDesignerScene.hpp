//
//  ParticleDesignerScene.hpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#ifndef ParticleDesignerScene_hpp
#define ParticleDesignerScene_hpp

#include <stdio.h>
#include "cocos2d.h"

class ParticleDesignerScene : public cocos2d::Layer {
public:
    
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(ParticleDesignerScene);
};

#endif /* ParticleDesignerScene_hpp */
