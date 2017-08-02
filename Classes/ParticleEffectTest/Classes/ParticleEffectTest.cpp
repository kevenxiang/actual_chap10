//
//  ParticleEffectTest.cpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#include "ParticleEffectTest.hpp"
USING_NS_CC;

Scene *ParticleEffectTest::createScene() {
    auto scene = Scene::create();
    auto layer = ParticleEffectTest::create();
    scene->addChild(layer);
    return scene;
}

bool ParticleEffectTest::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //    auto fire = ParticleFire::create(); // 火焰粒子系统
    //    auto fireworks = ParticleFireworks::create(); //烟花粒子系统
    //    auto flower = ParticleFlower::create(); //花朵粒子系统
    //    auto galaxy = ParticleGalaxy::create(); // 银河系粒子系统
    //    auto meteor = ParticleMeteor::create(); // 流星粒子系统
    //    auto rain = ParticleRain::create(); // 下雨粒子系统
    //    auto smoke = ParticleSmoke::create(); // 烟雾粒子系统
    //    auto snow = ParticleSnow::create(); // 下雪粒子系统
    //    auto spiral = ParticleSpiral::create(); // 螺旋粒子系统
    //    auto sun = ParticleSun::create(); // 太阳粒子系统
    
    
    // 创建爆炸粒子系统
    auto explosion = ParticleExplosion::create();
    // 设置爆炸粒子系统的位置
    explosion->setPosition(visibleSize.width/2, visibleSize.height/2);
    // 添加为当前层的子节点
    this->addChild(explosion);

    
    
//    auto fire = ParticleFire::create();
//    fire->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
//    this->addChild(fire);
    
    return true;
}
































