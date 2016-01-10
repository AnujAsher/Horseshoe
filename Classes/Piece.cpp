#include "Piece.h"
USING_NS_CC;
bool Piece::turn = false;
bool Piece::ended = false;
bool Piece::init()
{
    if (!Sprite::initWithFile("gfx/piece.png"))
        return false;
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(Piece::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Piece::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Piece::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(Piece::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}
bool Piece::onTouchBegan(Touch* touch, Event* event) {
	auto ai = dynamic_cast<HorseshoeMain*>(this->getParent())->getAI();
	bool p = UserDefault::getInstance()->getBoolForKey("Player");
    if (!ended
	&&this->getBoundingBox().containsPoint(touch->getLocation())
	&&turn==player
	&&(!ai||p==turn)){
        this->setOpacity(230);
        this->setScale(0.9f);
        return true;
	}
	return false;
}
void Piece::onTouchMoved(Touch* touch, Event* event) {
    if (this->getBoundingBox().containsPoint(touch->getLocation()))
    {
        this->setOpacity(230);
        this->setScale(0.9f);
	}
	else{
		this->setOpacity(255);
		this->setScale(1);
	}
};
void Piece::onTouchEnded(Touch* touch, Event* event) {
    if (this->getBoundingBox().containsPoint(touch->getLocation())){
			this->setOpacity(255);
			this->setScale(1);
			playPiece();
	}
};
void Piece::playPiece(){
	auto par = dynamic_cast<HorseshoeMain*>(this->getParent());
	if(par->isConnected(position)){
		auto ai = par->getAI();
		bool p = UserDefault::getInstance()->getBoolForKey("Player");
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		if(UserDefault::getInstance()->getBoolForKey("Sound",true))
			audio->playEffect("sfx/Move.wav");
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		int x = par->empty;
		par->empty = position;
		position = x;
		Vec2 np;
		switch(position){
			case 1: np = Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 + 180);
			break;
			case 2: np = Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 + 180);
			break;
			case 3: np = Vec2(origin.x + visibleSize.width/2, origin.y + 2*visibleSize.height/5);
			break;
			case 4: np = Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 - 180);
			break;
			case 5: np = Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 - 180);
			break;
		}
		auto move = MoveTo::create(0.4f, np);
		auto scaleup = ScaleTo::create(0.2f,1.4f);
		auto scaledown = ScaleTo::create(0.2f,1);
		auto scale = Sequence::createWithTwoActions(scaleup,scaledown);
		auto act = Spawn::createWithTwoActions(scale,move);
		this->runAction(act);
		CCLOG("%d to %d", par->empty, position);
		turn=!turn;	
		if(par->checkEnd(turn)){
			ended = true;
			par->setBGColor(Color3B(57,120,63));
			if(UserDefault::getInstance()->getBoolForKey("Sound",true)){
				if(ai&&turn!=p)
					audio->playEffect("sfx/Win.wav");
				else
					audio->playEffect("sfx/Lose.wav");
			}
		}
		else if(!turn)
			par->setBGColor(Color3B(156,48,47));
		else
			par->setBGColor(Color3B(56,92,120));
		if(ai&&turn!=p)
			par->playAI();
	}
}
void Piece::setPlayer(bool b, int p){
	if(!b)
		this->setColor(Color3B(156,48,47));
	else
		this->setColor(Color3B(56,92,120));
	player = b;
	position = p;
}
bool Piece::getTurn(){
	return turn;
}
void Piece::setTurn(bool b){
	turn = b;
	ended = false;
}
int Piece::getPos(){
	return position;
}
void Piece::setPos(int p){
	position = p;
}