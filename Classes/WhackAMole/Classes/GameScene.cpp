//
//  GameScene.cpp
//  actual_chap10
//
//  Created by xiang on 2017/7/31.
//
//

#include "GameScene.hpp"

Scene *Game::createScene() {
    auto scene = Scene::create();
    auto layer = Game::create();
    scene->addChild(layer);
    return scene;
}

bool Game::init() {
    if (!Layer::init()) {
        return false;
    }
    
    // 获得设备支持的可见OpenGL视图大小（即窗口大小）
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _screenWidth = visibleSize.width;
    _screenHeight = visibleSize.height;
    
    // 创建背景图片
    auto dirt = Sprite::createWithSpriteFrameName("bg_dirt.png");
    dirt->setScale(2.0);
    dirt->setPosition(Vec2(_screenWidth/2, _screenHeight/2));
    this->addChild(dirt, -2);
    
    // 创建上半部分草地
    auto upper = Sprite::createWithSpriteFrameName("grass_upper.png");
    upper->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    upper->setPosition(Vec2(_screenWidth/2, _screenHeight/2));
    this->addChild(upper, -1);
    
    // 创建下半部分草地
    auto lower = Sprite::createWithSpriteFrameName("grass_lower.png");
    lower->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    lower->setPosition(Vec2(_screenWidth/2, _screenHeight/2));
    this->addChild(lower, 1);
    
    // 创建左边的地鼠精灵
    auto leftMole = Sprite::createWithSpriteFrameName("mole_1.png");
    leftMole->setPosition(94, visibleSize.height / 2 - 60);
    this->addChild(leftMole, 0);
    _molesVector.pushBack(leftMole);
    
    // 创建中间的地鼠精灵
    auto centerMole = Sprite::createWithSpriteFrameName("mole_1.png");
    centerMole->setPosition(_screenWidth/ 2, _screenHeight / 2-60);
    this->addChild(centerMole, 0);
    _molesVector.pushBack(centerMole);
    
    // 创建右边的地鼠精灵
    auto rightMole = Sprite::createWithSpriteFrameName("mole_1.png");
    rightMole->setPosition(_screenWidth - 94, _screenHeight / 2-60);
    this->addChild(rightMole, 0);
    _molesVector.pushBack(rightMole);
    
//    _sucessScore = 15;
//    _totalMoles = 20;
    //根据关卡设置难度
    _sucessScore = 15 + (_level * 5 - 5);
    _totalMoles = 20 + (_level * 10 - 10);
    _timeBarInterval = 100/_totalMoles;
    _popDelay = 0.5 - (_level*0.05 - 0.05);
    
    //创建时间精灵
    auto clock = Sprite::createWithSpriteFrameName("clock.png");
    clock->setScale(0.3);
    clock->setPosition(_screenWidth * 0.2, _screenHeight * 0.1);
    this->addChild(clock, 2);
    //创建计时器进度条
    _timeBar = LoadingBar::create("bar.png");
    //由于图片大小关系，把scale设置成0.7
    _timeBar->setScale(0.7f);
    //设置进度条方向
    _timeBar->setDirection(LoadingBar::Direction::LEFT);
    //设置百分比
    _timeBar->setPercent(100);
    //设置进度条位置
    _timeBar->setPosition(Vec2(_screenWidth * 0.55, _screenHeight * 0.1));
    this->addChild(_timeBar, 2);
    
    
    // 每隔0.5秒调用一次随机弹出地鼠的函数
//    this->schedule(schedule_selector(Game::andomPopMoles), 0.5);
    this->schedule(schedule_selector(Game::andomPopMoles), _popDelay);
    this->schedule(schedule_selector(Game::gameOver), _popDelay);
    
    //创建单点触摸监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch *touch,Event *unused_event) {
        
        //把touch坐标转换成Node坐标
        Point touchLocation = this->convertTouchToNodeSpace(touch);
        //遍历地鼠集合
        for (Sprite *mole : _molesVector) {
            //如果当前这只地鼠的tag标记为0，表示不可以敲打，那么就直接检查下一个地鼠
            if (mole->getTag() == 0) {
                continue;
            }
            //如果touch触碰范围是地鼠
            if (mole->getBoundingBox().containsPoint(touchLocation)) {
                //创建木槌，将木槌显示在中间的地鼠头上
                auto mallet = Sprite::createWithSpriteFrameName("mallet1.png");
                //获得木槌动画
                auto malletAnimation = Animate::create(AnimationCache::getInstance()->getAnimation("malletAnimation"));
                mallet->setScale(0.8f);
                mallet->setPosition(mole->getPosition().x+60,mole->getPosition().y+60);
                this->addChild(mallet, 0);
                
                //播放木槌动画
                mallet->runAction(Sequence::create(malletAnimation, CallFunc::create([=]{
                    //播放地鼠被打中音效
                    SimpleAudioEngine::getInstance()->playEffect("ow.caf");
                    //地鼠被打中后播放粒子效果
                    auto aswoon = ParticleSystemQuad::create("aswoon.plist");
                    aswoon->setPosition(mole->getPosition().x, mole->getPosition().y);
                    this->addChild(aswoon);
                    //删除木槌
                    this->removeChild(mallet);
                    
                }), NULL));
                //地鼠被打中后，修改tag标记为0，表示地鼠已经被打中，不能重复敲打
                mole->setTag(0);
                //分数加1
                _score += 1;
                //地鼠被打中后，停止所有动作，既不能再执行大笑和眨眼的动作
                mole->stopAllActions();
                //播放地鼠被打中动画
                auto hitAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("hitAnimation"));
                //地鼠缩回地洞动作
                MoveBy *moveDown = MoveBy::create(0.2f, Point(0, -mole->getContentSize().height));
                EaseInOut *easeMoveDown = EaseInOut::create(moveDown, 3.0f);
                //地鼠顺序执行被打中动画和缩回地洞动作
                mole->runAction(Sequence::create(hitAnimate, easeMoveDown, NULL));
            }
        }
        
        return true;
    };
    
    //添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //关卡数
    std::string levelString = StringUtils::format("关卡: %i", _level);
    _levelLabel = Label::createWithSystemFont(levelString, "fonts/Marker Felt.ttf", 10);
    _levelLabel->setPosition(Vec2(visibleSize.width * 0.10, visibleSize.height - 30));
    this->addChild(_levelLabel, 3);
    
    //关卡得分
    _scoreLabel = Label::createWithSystemFont("本关得分: 0", "fonts/Marker Felt.ttf", 10);
    _scoreLabel->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height - 30));
    this->addChild(_scoreLabel, 10);
    
    //关卡地鼠总数
    std::string moleLabelString = StringUtils::format("本关地鼠: %i", _totalMoles);
    _moleLabel = Label::createWithSystemFont(moleLabelString, "fonts/Marker Felt.ttf", 10);
    _moleLabel->setPosition(Vec2(visibleSize.width * 0.55, visibleSize.height - 30));
    this->addChild(_moleLabel, 10);
    
    //关卡过关分数
    std::string passLabelString = StringUtils::format("过关目标分: %i", _sucessScore);
    _passLabel = Label::createWithSystemFont(passLabelString, "fonts/Marker Felt.ttf", 10);
    _passLabel->setPosition(Vec2(visibleSize.width * 0.85, visibleSize.height - 30));
    this->addChild(_passLabel, 10);
    
    return true;
}

//地鼠随机钻出
void Game::andomPopMoles(float delta) {
    
    // _gameOver标记为true，游戏结束
    if (_gameOver) {
        return;
    }
    
    //设置分数
    _scoreLabel->setString(StringUtils::format("本关得分: %d", _score));
    
    //循环地鼠集合
    for (auto mole : _molesVector) {
        //获取一个随机数，如果随机数取模3等于0的话，则准备弹出地鼠
        int temp = CCRANDOM_0_1() * 10000;
        if (temp % 3 == 0) {
            
            // getNumberOfRunningActions等于0，说明该地鼠并没有执行动作，也就是还没有钻出来，如果不等于0，说明地鼠已经钻出来了，则不再让地鼠钻出来
            if (mole->getNumberOfRunningActions() == 0) {
                //地鼠钻出
                popMole(mole);
                //计时器进度条减少
                float percentage = _timeBarInterval * _totalMoles;
                // 如果时间不长了，将进度条设置成红色
                if (_totalMoles == 9) {
                    _timeBar->setColor(Color3B(255, 0, 0));
                    // 播放秒针走动的声音，增加游戏时间紧迫感
                    SimpleAudioEngine::getInstance()->playEffect("second.mp3", true);
                }
                _timeBar->setPercent(percentage);
            }
        }
    }
}

void Game::popMole(Sprite *mole) {
    
    // 每钻出一个地鼠，地鼠总数减1，当钻出的地鼠超过设定的地鼠总数时，函数结束
    if (_totalMoles <= 0) {
        return;
    }
    _totalMoles--;
    
    // 如果地鼠上一次被打中了，再钻出来的时候，还会显示被打中。所以在它每次从洞里钻出来的时候，设置它的显示帧为初使图片。
    mole->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mole_1.png"));
    
    // 1.创建一个action，让地鼠沿着Y轴钻洞来。
    auto moveUp = MoveBy::create(0.2f, Point(0, mole->getContentSize().height));
    
    // 2.为了使得移动更加真实，上面的action用一个EaseInOut动作包装起来了。这会使得钻洞的动作在开始和结束的时候速度比较慢，看起来，就好像地鼠在加速和减速一样。
    auto easeMoveUp = EaseInOut::create(moveUp, 3.0f);
     // 3.创建一个action，使地鼠能够钻回去。这里通过调用action的reverse方法，得到相反的action。
    auto easeMoveDown = easeMoveUp->reverse();
    
    //延迟动作
//    auto delay = DelayTime::create(0.5);
    //在地鼠钻出来以后，播放地鼠大笑的动画
    auto laughAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("laughAnimation"));
    // 5.地鼠按顺序执行之前设计的几个动作
    mole->runAction(Sequence::create(easeMoveUp, CallFuncN::create(CC_CALLBACK_1(Game::setHit, this)), laughAnimate, easeMoveDown, CallFuncN::create(CC_CALLBACK_1(Game::unHit, this)) , NULL));

}

//在地鼠笑时，设置可以敲打地鼠
void Game::setHit(cocos2d::Ref *pSender) {
    Sprite *mole = (Sprite *)pSender;
    mole->setTag(1);
    //播放地鼠“笑”的音效
    SimpleAudioEngine::getInstance()->playEffect("laugh.caf");
}

//在地鼠笑完之后，设置不可以敲打地鼠
void Game::unHit(cocos2d::Ref *pSender) {
    Sprite *mole = (Sprite *)pSender;
    mole->setTag(0);
}

void Game::gameOver(float delta) {
    
    // 判断_totalMoles是否小于0，小于0表示本关卡所有地鼠都已经钻出
    if (_totalMoles <= 0) {
        // 判断当所有地鼠都缩回地洞时，停止音效和背景音乐，显示菜单
        bool flag = true;
        for (Sprite *mole : _molesVector) {
            if (mole->getNumberOfRunningActions() != 0) {
                flag = false;
                break;
            }
        }
        
        if (flag) {
            _gameOver = true;
            // 当前分数小于过关分数，游戏失败
            MenuItemImage *goItem = nullptr;
            if (_score < _sucessScore) {
                // 当前分数小于过关分数，游戏失败，菜单项为继续挑战
                goItem = MenuItemImage::create("btn-continue.png", "btn-continue.png", [&](Ref *sender){
                    Director::getInstance()->replaceScene(Game::createScene());
                });
            } else {
                // 当前分数大于过关分数，过关，菜单项为进入下一关
                goItem = MenuItemImage::create("btn-next.png", "btn-next.png", [&](Ref *sender){
                    // 游戏关卡加1
                    _level = _level+1;
                    Director::getInstance()->replaceScene(Game::createScene());
                });
            }
            
            goItem->setPosition(Vec2(_screenWidth/2, _screenHeight/2+50));
            
            // 重头再来菜单项
            auto againItem = MenuItemImage::create("btn-again.png", "btn-again.png", [&](Ref *sender){
                Director::getInstance()->replaceScene(Start::createScene());
            });
            againItem->setPosition(Vec2(_screenWidth/2, _screenHeight/2 - 100));
            
            // 停止背景音乐和音效
            SimpleAudioEngine::getInstance()->stopAllEffects();
            SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            
            // 添加菜单项
            auto menu = Menu::create(goItem, againItem, NULL);
            // 设置菜单在屏幕的位置
            menu->setPosition(Vec2::ZERO);
            // 将菜单添加到当前层的子节点
            this->addChild(menu, 1);
            return;
        }
    }

}






















