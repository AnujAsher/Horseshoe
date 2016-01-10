#include "Settings.h"
USING_NS_CC;
bool Settings::init()
{
    if ( !Scene::init() )
        return false;
    ud = UserDefault::getInstance();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event *event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            auto scene = HorseshoeMenu::create();
            ud->flush();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(57,120,63)));
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    sound = ud->getBoolForKey("Sound",true);
    play = ud->getBoolForKey("Player");
    dif = ud->getIntegerForKey("Difficulty",0);
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
    auto bgMain = LayerColor::create(Color4B(0,0,0,64),800,420);
    bgMain->setAnchorPoint(Vec2(0.5,0.5));
    bgMain->ignoreAnchorPointForPosition(false);
    bgMain->setPosition(Vec2(origin.x + visibleSize.width/2,340));
    this->addChild(bgMain);
    auto bgFooter = LayerColor::create(Color4B(0,0,0,64),473,80);
    bgFooter->setAnchorPoint(Vec2(0.5,0.5));
    bgFooter->ignoreAnchorPointForPosition(false);
    bgFooter->setPosition(Vec2(origin.x + visibleSize.width/2,60));
    this->addChild(bgFooter);
    auto header = Label::createWithTTF("Settings", "fonts/font.ttf", 90, Size::ZERO, TextHAlignment::CENTER);
    header->setPosition(Vec2(origin.x + visibleSize.width/2,630));
    this->addChild(header);
    auto soundLabel = Label::createWithTTF("Sounds", "fonts/font.ttf", 67);
    soundLabel->setAnchorPoint(Vec2(0,0.5));
    soundLabel->setPosition(Vec2(origin.x + visibleSize.width/2 - 350,480));
    this->addChild(soundLabel);
    auto difLabel = Label::createWithTTF("Difficulty", "fonts/font.ttf", 67);
    difLabel->setAnchorPoint(Vec2(0,0.5));
    difLabel->setPosition(Vec2(origin.x + visibleSize.width/2 - 350,340));
    this->addChild(difLabel);
    auto playLabel = Label::createWithTTF("Play as", "fonts/font.ttf", 67);
    playLabel->setAnchorPoint(Vec2(0,0.5));
    playLabel->setPosition(Vec2(origin.x + visibleSize.width/2 - 350,200));
    this->addChild(playLabel);
    soundButton = ui::Button::create();
    if (sound)
        soundButton->setTitleText("On");
    else
        soundButton->setTitleText("Off");
    soundButton->setTitleFontSize(67);
    soundButton->setTitleFontName("fonts/font.ttf");
    soundButton->setAnchorPoint(Vec2(1,0.5));
    soundButton->setPosition(Vec2(origin.x + visibleSize.width/2 + 350,480));
    soundButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            sound = !sound;
            if (sound)
                soundButton->setTitleText("On");
            else
                soundButton->setTitleText("Off");
            ud->setBoolForKey("Sound",sound);
			if(sound)
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/Select.wav");
        }
    });
    this->addChild(soundButton);
    difButton = ui::Button::create();
	switch(dif){
	case -1:
        difButton->setTitleText("Easy");
		break;
	case 0:
        difButton->setTitleText("Medium");
		break;
	case 1:
        difButton->setTitleText("Hard");
		break;
	}
    difButton->setTitleFontSize(67);
    difButton->setTitleFontName("fonts/font.ttf");
    difButton->setAnchorPoint(Vec2(1,0.5));
    difButton->setPosition(Vec2(origin.x + visibleSize.width/2 + 350,340));
    difButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            dif = ((dif+2)%3)-1;
			switch(dif){
				case -1:
					difButton->setTitleText("Easy");
					break;
				case 0:
					difButton->setTitleText("Medium");
					break;
				case 1:
					difButton->setTitleText("Hard");
					break;
			}
            ud->setIntegerForKey("Difficulty",dif);
			if(sound)
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/Select.wav");
        }
    });
    this->addChild(difButton);
    playButton = ui::Button::create();
    if (play)
        playButton->setTitleText("Blue");
    else
        playButton->setTitleText("Red");
    playButton->setTitleFontSize(67);
    playButton->setTitleFontName("fonts/font.ttf");
    playButton->setAnchorPoint(Vec2(1,0.5));
    playButton->setPosition(Vec2(origin.x + visibleSize.width/2 + 350,200));
    playButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            play = !play;
            if (play)
                playButton->setTitleText("Blue");
            else
                playButton->setTitleText("Red");
            ud->setBoolForKey("Player",play);
			if(sound)
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/Select.wav");
        }
    });
    this->addChild(playButton);
    resetButton = ui::Button::create();
	resetButton->setTitleText("Reset Defaults");
    resetButton->setTitleFontSize(56);
    resetButton->setTitleFontName("fonts/font.ttf");
    resetButton->setPosition(Vec2(origin.x + visibleSize.width/2,60));
    resetButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            sound = true;
			soundButton->setTitleText("On");
            ud->setBoolForKey("Sound",sound);
			dif = 0;
			difButton->setTitleText("Medium");
			ud->setIntegerForKey("Difficulty",dif);
            play = false;
			playButton->setTitleText("Red");
            ud->setBoolForKey("Player",play);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/Select.wav");
        }
    });
    this->addChild(resetButton);
    return true;
}