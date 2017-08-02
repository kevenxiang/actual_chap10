//
//  ParticleDesignerScene.cpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#include "ParticleDesignerScene.hpp"

USING_NS_CC;

Scene *ParticleDesignerScene::createScene() {
    auto scene = Scene::create();
    auto layer = ParticleDesignerScene::create();
    scene->addChild(layer);
    return scene;
}

bool ParticleDesignerScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 使用plist文件创建一个粒子
    auto water = ParticleSystemQuad::create("water.plist");
    water->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 0.8));
    this->addChild(water);
    
    return true;
}
