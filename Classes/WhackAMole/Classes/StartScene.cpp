//
//  StartScene.cpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#include "StartScene.hpp"

USING_NS_CC;

Scene *Start::createScene() {
    auto scene = Scene::create();
    auto layer = Start::create();
    scene->addChild(layer);
    return scene;
}

bool Start::init() {
    
    //调用父类的init函数
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //创建背景图片
    auto dirt = Sprite::create("bg_dirt.png");
    dirt->setScale(2.0f);
    dirt->setAnchorPoint(Vec2::ZERO);
    dirt->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(dirt, -2);
    
    //创建上半部分草地
    auto upper = Sprite::create("grass_upper.png");
    upper->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    upper->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(upper, -1);
    
    // 创建下半部分草地
    auto lower = Sprite::create("grass_lower.png");
    lower->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    lower->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(lower, 1);
    
    //创建左边的地鼠精灵
    auto leftMole = Sprite::create("mole_1.png");
    leftMole->setPosition(Vec2(94, visibleSize.height/2 - 30));
    this->addChild(leftMole, 0);
    
    // 创建中间的地鼠精灵
    auto centerMole = Sprite::create("mole_thump4.png");
    centerMole->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(centerMole, 0);
    
    // 创建右边的地鼠精灵
    auto rightMole = Sprite::create("mole_laugh1.png");
    rightMole->setPosition(Vec2(visibleSize.width - 94, visibleSize.height/2 - 20));
    this->addChild(rightMole, 0);
    
    // 创建木槌，将木槌显示在中间的地鼠头上
    auto mallet = Sprite::create("mallet2.png");
    mallet->setScale(0.8f);
    mallet->setPosition(Vec2(visibleSize.width/2+80, visibleSize.height/2+80));
    this->addChild(mallet, 0);
    
    // “疯狂打地鼠”logo
    auto label1 = Label::createWithSystemFont("疯狂打地鼠", "Arial-BoldMT", 12);
    label1->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.90));
    label1->setColor(Color3B(255, 0, 0));
    this->addChild(label1, 1);
    
    // 公司名
    auto label2 = Label::createWithSystemFont("疯狂软件教育中心", "Arial-BoldMT", 8);
    label2->setPosition(visibleSize.width/2, visibleSize.height*0.20);
    this->addChild(label2,1);
    
    // 网址
    auto label3 = Label::createWithSystemFont("www.fkit.org", "Arial-BoldMT", 8);
    label3->setPosition(visibleSize.width/2, visibleSize.height*0.15);
    this->addChild(label3,1);
    
    // 开始按钮，点击时调用startGame函数
    auto playItem = MenuItemImage::create("btn-start.png", "btn-start.png", CC_CALLBACK_0(Start::startGame, this));
    playItem->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.3));
    
    // 创建一个关闭图标（MenuItemImage）
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Start::menuCloseCallback, this));
    // 设置关闭图标的位置
    closeItem->setPosition(Vec2(visibleSize.width - closeItem->getContentSize().width/2, closeItem->getContentSize().height/2));
    
    // 创建一个菜单项（Menu）
    auto menu = Menu::create(playItem, closeItem, NULL);
    // 设置菜单项在屏幕的位置
    menu->setPosition(Vec2::ZERO);
    // 将菜单项添加到当前层的子节点
    this->addChild(menu, 1);
    
    // 播放背景音乐并设置背景音乐音量大小
    SimpleAudioEngine::getInstance()->playBackgroundMusic("whack.caf", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3);
    
    return true;
}

void Start::startGame() {
    //将精灵表单添加到缓存
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BACKGROUNDPLIST);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(RESOURCESPLIST);
    
    //预加载背景音乐和音效
    SimpleAudioEngine::getInstance()->preloadEffect(LAUGHEFFECT);
    SimpleAudioEngine::getInstance()->preloadEffect(OWEFFECT);
    SimpleAudioEngine::getInstance()->preloadEffect(SECONDEFFECT);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUNDMUSIC);
    
    // 创建需要使用的动画，并保存在缓存当中，准备之后使用
    // 地鼠笑的动画
    Animation *laughAnimation = getAnimationByName("mole_laugh", 0.5f, 3);
    // 地鼠被击中的动画
    Animation *hitAnimation = getAnimationByName("mole_thump", 0.3f, 4);
    // 木槌动画
    Animation *malletAnimation = getAnimationByName("mallet", 0.15f, 3);
    AnimationCache::getInstance()->addAnimation(laughAnimation, "laughAnimation");
    AnimationCache::getInstance()->addAnimation(hitAnimation, "hitAnimation");
    AnimationCache::getInstance()->addAnimation(malletAnimation, "malletAnimation");
    
    // 关闭背景音乐
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    //切换到游戏主画面
    Director::getInstance()->replaceScene(Game::createScene());
}

/**
 * 获得动画动作函数
 * animName：动画帧的名字
 * delay：动画帧与帧之间的间隔时间
 * animNum：动画帧的数量
 */
Animation *Start::getAnimationByName(std::string animName, float delay, int animNum) {
    Animation *animation = Animation::create();
    // 循环从精灵帧缓存中获取与图片名称相对应的精灵帧组成动画
    for (unsigned int i = 1; i <= animNum; i++) {
        // 获取动画图片名称，例如plane0.png
        std::string frameName = animName;
        frameName.append(StringUtils::format("%d",i)).append(".png");
        // 将单张图片添加为精灵帧（即动画帧）
        animation->addSpriteFrameWithFile(frameName.c_str());
    }
    // 设置动画播放的属性
    animation->setDelayPerUnit(delay);
    // 让精灵对象在动画执行完后恢复到最初状态
    animation->setRestoreOriginalFrame(true);
    return animation;
}


void Start::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


























