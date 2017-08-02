//
//  MyParticle.cpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#include "MyParticle.hpp"
USING_NS_CC;

MyParticle *MyParticle::create() {
    MyParticle *ret = new MyParticle();
    // 初始化350个粒子
    if (ret && ret->initWithTotalParticles(350)) {
        ret->autorelease();
        return ret;
    } else {
        CC_SAFE_DELETE(ret);
    }
    
    return nullptr;
}

bool MyParticle::initWithTotalParticles(int numberOfParticles) {
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles)) {
        // 粒子发射器的持续时间，kCCParticleDurationInfinity表示粒子效果永远持续下去
        setDuration(ParticleSystem::DURATION_INFINITY);
        // 发射器模式：重力模式（kCCParticleModeGravity）、半径模式（kCCParticleModeRadius）
        setEmitterMode(ParticleSystem::Mode::GRAVITY);
        //        setEmitterMode(ParticleSystem::Mode::RADIUS);
        if (getEmitterMode() == ParticleSystem::Mode::GRAVITY) {
            setSourcePosition(Vec2(-10, 0));
            // gravity：粒子在x轴和y轴的加速度
            setGravity(Vec2(0, -90));
            // radialAccel：粒子的径向加速度
            setRadialAccel(0);
            // 粒子间的径向加速度差异
            setRadialAccelVar(0);
            // tangentialAccel：粒子的切向加速度
            setTangentialAccel(100);
            // 粒子间的切向加速度差异
            setTangentialAccelVar(10);
            // speed：粒子的运动速度
            setSpeed(150);
            // 粒子的速度差异
            setSpeedVar(50);
        } else {
            // startRadius：所发射粒子和粒子效果节点位置间的距离
            setStartRadius(120);
            // 粒子间开始半径差异
            setStartRadiusVar(0);
            // endRadius：粒子要旋转到的位置和节点位置间的距离
            setEndRadius(10);
            // 粒子间结束半径差异
            setEndRadiusVar(0);
            // rotatePerSecond影响粒子移动的方向、速度
            setRotatePerSecond(-150);
            // 粒子间每秒的旋转角度差异
            setRotatePerSecondVar(0);
        }
        
        // 设置粒子发射器的位置和位置类型
        setPosVar(Point::ZERO);
        setPositionType(ParticleSystem::PositionType::FREE);
        // 粒子发射的方向
        setAngle(80);
        setAngleVar(20);
        // 粒子的生命周期
        setLife(2.0f);
        setLifeVar(1.0f);
        // 每一帧所发射的粒子数量
        setEmissionRate(getTotalParticles()/getLife());
        // 粒子的颜色
        setStartColor(Color4F(1.0f, 1.0f, 1.0f, 1.0f));
        setStartColorVar(Color4F(0.5f, 0.5f, 0.5f, 0.5f));
        setEndColor(Color4F(0.2f, 0.2f, 0.2f, 0.2f));
        setEndColorVar(Color4F(0.1f, 0.1f, 0.1f, 0.1f));
        // 设置粒子大小，单位是像素
        setStartSize(6.0f);
        setStartSizeVar(2.0f);
        // START_SIZE_EQUAL_TO_END_SIZE使粒子大小在其生命周期中不发生变化
        setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);
        setEndSizeVar(0);
        // 粒子的纹理fire.png
        setTexture(Director::getInstance()->getTextureCache()->addImage("fire.png"));
        // 粒子的混合模式
        setBlendFunc((BlendFunc){GL_SRC_ALPHA,GL_DST_ALPHA});
        setBlendAdditive(false);
        
        return true;
        
    }
    
    return false;
}



























