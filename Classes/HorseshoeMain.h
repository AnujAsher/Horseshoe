#pragma once
#include "HorseshoeMenu.h"
#include "Piece.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

class Piece;
class HorseshoeMain : public cocos2d::Scene
{
public:
    virtual bool init();    
    CREATE_FUNC(HorseshoeMain);
	virtual void onEnterTransitionDidFinish();
	void setBGColor(cocos2d::Color3B);
	bool isConnected(int);
	bool checkEnd(bool);
	void setAI(bool);
	int empty;
	bool getAI();
	void playAI();
private:
	int sred, sblu, dif;
	void resetGame();
	void setScoreLabel(int, cocos2d::Label*);
	bool ai, player;
	cocos2d::LayerColor *bgLayer;
	cocos2d::Label *redScore, *bluScore;
	Piece *p11, *p12, *p21, *p22;
};


