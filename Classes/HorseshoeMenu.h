#pragma once
#include "cocos2d.h"
#include "HorseshoeMain.h"
#include "Settings.h"
#include "Info.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif
class HorseshoeMenu : public cocos2d::Scene
{
public:
    virtual bool init();
    CREATE_FUNC(HorseshoeMenu);
private:
};