//
//  MyParticleScene.cpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#include "MyParticleScene.hpp"
#include "MyParticle.hpp"

USING_NS_CC;

Scene *MyParticleScene::createScene() {
    auto scene = Scene::create();
    auto layer = MyParticleScene::create();
    scene->addChild(layer);
    return scene;
}

bool MyParticleScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 测试自定义粒子系统
    auto particle = MyParticle::create();
    particle->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(particle);
    
    return true;
}
