#include "HorseshoeMenu.h"
USING_NS_CC;
bool HorseshoeMenu::init()
{
    if ( !Scene::init() )
        return false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event *event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            Director::getInstance()->end();
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    auto bgLayer = LayerColor::create(Color4B(57,120,63,255),1280,720);
    bgLayer->setAnchorPoint(Vec2(0.5,0.5));
    bgLayer->ignoreAnchorPointForPosition(false);
    bgLayer->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height/2));
    this->addChild(bgLayer);
    auto bgHeader = LayerColor::create(Color4B(0,0,0,64),520,120);
    bgHeader->setAnchorPoint(Vec2(0.5,0.5));
    bgHeader->ignoreAnchorPointForPosition(false);
    bgHeader->setPosition(Vec2(origin.x + visibleSize.width/2,630));
    this->addChild(bgHeader);
    auto bgMain = LayerColor::create(Color4B(0,0,0,64),520,420);
    bgMain->setAnchorPoint(Vec2(0.5,0.5));
    bgMain->ignoreAnchorPointForPosition(false);
    bgMain->setPosition(Vec2(origin.x + visibleSize.width/2,320));
    this->addChild(bgMain);
    auto header = Label::createWithTTF("Horseshoe", "fonts/font.ttf", 90);
    header->setPosition(Vec2(origin.x + visibleSize.width/2,630));
    this->addChild(header);
    auto singlePlayer = ui::Button::create();
    singlePlayer->setTitleText("One Player");
    singlePlayer->setTitleFontSize(56);
    singlePlayer->setTitleFontName("fonts/font.ttf");
    singlePlayer->setZoomScale(0.2f);
    singlePlayer->setPosition(Vec2(origin.x + visibleSize.width/2,460));
    singlePlayer->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
			if(UserDefault::getInstance()->getBoolForKey("Sound",true))
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/Select.wav");
            auto next = HorseshoeMain::create();
			next->setAI(true);
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, next, Color3B(57,120,63)));
        }
    });
    this->addChild(singlePlayer);
    auto localMP = ui::Button::create();
    localMP->setTitleText("Two Players");
    localMP->setTitleFontSize(56);
    localMP->setTitleFontName("fonts/font.ttf");
    localMP->setZoomScale(0.2f);
    localMP->setPosition(Vec2(origin.x + visibleSize.width/2,320));
    localMP->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
			if(UserDefault::getInstance()->getBoolForKey("Sound",true))
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/Select.wav");
            auto next = HorseshoeMain::create();
			next->setAI(false);
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, next, Color3B(57,120,63)));
        }
    });
    this->addChild(localMP);
    auto settings = ui::Button::create();
    settings->setTitleText("Settings");
    settings->setTitleFontSize(56);
    settings->setTitleFontName("fonts/font.ttf");
    settings->setZoomScale(0.2f);
    settings->setPosition(Vec2(origin.x + visibleSize.width/2,180));
    settings->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
			if(UserDefault::getInstance()->getBoolForKey("Sound",true))
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/Select.wav");
            auto next = Settings::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, next, Color3B(57,120,63)));
        }
    });
    this->addChild(settings);
    auto info = ui::Button::create("gfx/info.png");
    info->setZoomScale(0.2f);
    info->setPosition(Vec2(origin.x + info->getContentSize().width, origin.y + info->getContentSize().height));
    info->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
			if(UserDefault::getInstance()->getBoolForKey("Sound",true))
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/Select.wav");
            auto next = Info::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, next, Color3B(57,120,63)));
        }
    });
    auto bgInfo = LayerColor::create(Color4B(0,0,0,64),100,100);
    bgInfo->setAnchorPoint(Vec2(0.5,0.5));
    bgInfo->ignoreAnchorPointForPosition(false);
    bgInfo->setPosition(info->getPosition());
    this->addChild(bgInfo);
    this->addChild(info);
    auto share = ui::Button::create("gfx/share.png");
    share->setZoomScale(0.2f);
    share->setPosition(Vec2(origin.x + visibleSize.width - share->getContentSize().width, origin.y + share->getContentSize().height));
    share->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
			if(UserDefault::getInstance()->getBoolForKey("Sound",true))
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/Select.wav");
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "callShare", "()V")) {
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }
    });
    auto bgShare = LayerColor::create(Color4B(0,0,0,64),100,100);
    bgShare->setAnchorPoint(Vec2(0.5,0.5));
    bgShare->ignoreAnchorPointForPosition(false);
    bgShare->setPosition(share->getPosition());
    this->addChild(bgShare);
    this->addChild(share);
    return true;
}