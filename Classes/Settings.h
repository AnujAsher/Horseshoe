#pragma once
#include "HorseshoeMenu.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
class Settings : public cocos2d::Scene
{
public:
    virtual bool init();
    CREATE_FUNC(Settings);
private:
    bool sound, play;
	int dif;
    cocos2d::ui::Button *soundButton, *playButton, *difButton, *resetButton;
    cocos2d::UserDefault *ud;
};