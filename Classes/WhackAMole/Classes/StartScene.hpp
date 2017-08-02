//
//  StartScene.hpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#ifndef StartScene_hpp
#define StartScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.hpp"

USING_NS_CC;
using namespace CocosDenshion;

// 游戏的精灵表单、背景音乐和音效
#define BACKGROUNDPLIST "background.plist"
#define RESOURCESPLIST "resources.plist"
#define LAUGHEFFECT "laugh.caf"
#define OWEFFECT "ow.caf"
#define SECONDEFFECT "second.mp3"
#define BACKGROUNDMUSIC "whack.caf"

class Start : public cocos2d::Layer {
public:
    /**
     * 静态函数，创建Scene场景
     * 注意：在Cocos2d-x中没有Cocos2d-iPhone中的“id”,建议返回类实例的指针
     */
    static cocos2d::Scene *createScene();
    
    /**
     * init函数，完成初始化操作。
     * 注意：init函数在Cocos2d-x中返回bool值，而不是返回Cocos2d-iPhone中的“id”
     */
    virtual bool init();
    
    // 开始游戏函数
    void startGame();
    
    /**
     获得动画函数
     第一个参数：动画名称
     第二个参数：间隔事件
     第三个参数：动画图片数量
     */
    Animation* getAnimationByName(std::string animName,float delay,int animNum);
    
    // 选择器回调函数
    void menuCloseCallback(Ref* pSender);
    
    /**
     * 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
     */
    CREATE_FUNC(Start);
    
};

#endif /* StartScene_hpp */
