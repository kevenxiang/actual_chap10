//
//  GameScene.hpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "StartScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace CocosDenshion;

USING_NS_CC;
using namespace ui;

static int _level = 1;  // 当前关卡数

class Game : public cocos2d::Layer {
    
private:
    int _screenWidth, _screenHeight;  // 屏幕宽度和高度
    Vector<Sprite *> _molesVector;  //地鼠集合
    Label* _levelLabel; // 关卡数的Label
    Label* _passLabel; // 过关分数的Label
    Label* _scoreLabel; // 显示分数的Label
    Label* _moleLabel; // 显示地鼠总数的Label
    int _score;  // 分数
    
    int _sucessScore; // 过关目标分数
    int _totalMoles; // 当前关卡总共钻出地鼠数量
    LoadingBar* _timeBar; // 计时器进度条
    float _timeBarInterval; // 时间条间隔
    
    float _popDelay; // 随机弹出地鼠的时间
    bool _gameOver; // 游戏是否结束
    
public:
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    // 随机钻出地鼠
    void andomPopMoles(float delta);
    
    // 钻出地鼠
    void popMole(Sprite *mole);
    
    // 设置可以敲打地鼠
    void setHit(Ref *pSender);
    
    // 设置不可以敲打地鼠
    void unHit(Ref* pSender);
    
    // 游戏结束
    void gameOver(float delta);
    
    /**
     * 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
     */
    CREATE_FUNC(Game);


};

#endif /* GameScene_hpp */

























