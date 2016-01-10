#include "Info.h"
USING_NS_CC;
bool Info::init()
{
    if ( !Scene::init() )
        return false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event *event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            auto scene = HorseshoeMenu::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(57,120,63)));
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
    auto bgMain = LayerColor::create(Color4B(0,0,0,64),890,320);
    bgMain->setAnchorPoint(Vec2(0.5,0.5));
    bgMain->ignoreAnchorPointForPosition(false);
    bgMain->setPosition(Vec2(origin.x + visibleSize.width/2,360));
    this->addChild(bgMain);
    auto bgFooter = LayerColor::create(Color4B(0,0,0,64),820,60);
    bgFooter->setAnchorPoint(Vec2(0.5,0.5));
    bgFooter->ignoreAnchorPointForPosition(false);
    bgFooter->setPosition(Vec2(origin.x + visibleSize.width/2,120));
    this->addChild(bgFooter);
    auto header = Label::createWithTTF("About", "fonts/font.ttf", 90, Size::ZERO, TextHAlignment::CENTER);
    header->setPosition(Vec2(origin.x + visibleSize.width/2,630));
    this->addChild(header);
    auto mainLabel = Label::createWithTTF("Horseshoe is a two player game.\n\nThe players take turns to move their\npieces along the lines until one of\nthem has no moves available.", "fonts/font.ttf", 50, Size::ZERO, TextHAlignment::CENTER);
    mainLabel->setPosition(Vec2(origin.x + visibleSize.width/2,360));
    this->addChild(mainLabel);
    auto footer = Label::createWithTTF("© 2015 Yet Another Game Dev. All rights reserved.", "fonts/font.ttf", 34, Size::ZERO, TextHAlignment::CENTER);
    footer->setPosition(Vec2(origin.x + visibleSize.width/2,120));
    this->addChild(footer);
    return true;
}