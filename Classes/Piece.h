#pragma once
#include "HorseshoeMain.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class Piece : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(Piece);
	void setPlayer(bool, int);
	static bool getTurn();
	static void setTurn(bool);
	int getPos();
	void setPos(int);
	void playPiece();
private:
	static bool turn, ended;
	bool player;
	int position;
    bool onTouchBegan(cocos2d::Touch* , cocos2d::Event*);
    void onTouchMoved(cocos2d::Touch* , cocos2d::Event*);
    void onTouchEnded(cocos2d::Touch* , cocos2d::Event*);
};