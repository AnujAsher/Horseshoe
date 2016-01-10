#include "HorseshoeMain.h"
USING_NS_CC;
bool HorseshoeMain::init()
{
    if ( !Scene::init() )
        return false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event *event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
			CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
            auto scene = HorseshoeMenu::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(57,120,63)));
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	bgLayer = LayerColor::create(Color4B(57,120,63,255),1280,720);
    bgLayer->setAnchorPoint(Vec2(0.5,0.5));
    bgLayer->ignoreAnchorPointForPosition(false);
    bgLayer->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height/2));
    this->addChild(bgLayer);
 	auto board = DrawNode::create();
	board->drawSegment(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 +180), Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 - 180), 12, Color4F::WHITE);
	board->drawSegment(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 -180), Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 + 180), 12, Color4F::WHITE);
	board->drawSegment(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 +180), Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 - 180), 12, Color4F::WHITE);
	board->drawSegment(Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 +180), Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 - 180), 12, Color4F::WHITE);
	board->drawSegment(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 -180), Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 - 180), 12, Color4F::WHITE);
	board->drawSolidCircle(Vec2(origin.x + visibleSize.width/2, origin.y + 2*visibleSize.height/5), 65, 0, 250, Color4F::WHITE);
	board->drawSolidCircle(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 +180), 65, 0, 250, Color4F::WHITE);
	board->drawSolidCircle(Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 + 180), 65, 0, 250, Color4F::WHITE);
	board->drawSolidCircle(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 - 180), 65, 0, 250, Color4F::WHITE);
	board->drawSolidCircle(Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 - 180), 65, 0, 250, Color4F::WHITE);
	this->addChild(board);
	empty = 3;
	p11=Piece::create();
	p11->setPlayer(false, 1);
	p11->setPosition(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 + 180));
	this->addChild(p11);
	p12=Piece::create();
	p12->setPlayer(false, 5);
	p12->setPosition(Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 - 180));
	this->addChild(p12);
	p21=Piece::create();
	p21->setPlayer(true, 2);
	p21->setPosition(Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 + 180));
	this->addChild(p21);
	p22=Piece::create();
	p22->setPlayer(true, 4);
	p22->setPosition(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 - 180));
	this->addChild(p22);
    auto redHeader = Label::createWithTTF("Red", "fonts/font.ttf", 72, Size::ZERO, TextHAlignment::CENTER);
    redHeader->setPosition(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + visibleSize.height - 3*redHeader->getContentSize().height/4));
    this->addChild(redHeader);
    redScore = Label::createWithTTF("0", "fonts/font.ttf", 72, Size::ZERO, TextHAlignment::CENTER);
    redScore->setPosition(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + visibleSize.height - 2*redScore->getContentSize().height));
    this->addChild(redScore);
    auto bluHeader = Label::createWithTTF("Blu", "fonts/font.ttf", 72, Size::ZERO, TextHAlignment::CENTER);
    bluHeader->setPosition(Vec2(origin.x + visibleSize.width/2 + 180, origin.y + visibleSize.height - 3*bluHeader->getContentSize().height/4));
    this->addChild(bluHeader);
	bluScore = Label::createWithTTF("0", "fonts/font.ttf", 72, Size::ZERO, TextHAlignment::CENTER);
    bluScore->setPosition(Vec2(origin.x + visibleSize.width/2 + 180, origin.y + visibleSize.height - 2*bluScore->getContentSize().height));
    this->addChild(bluScore);
	auto resetButton = ui::Button::create("gfx/reset.png");
    resetButton->setPosition(Vec2(origin.x + visibleSize.width/2,620));
	resetButton->setScale(0.15f);
    resetButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
			this->resetGame();
        }
    });
    this->addChild(resetButton);
	sred = 0;
	sblu = 0;
    return true;
}
void HorseshoeMain::onEnterTransitionDidFinish(){
	Scene::onEnterTransitionDidFinish();
	resetGame();
}
void HorseshoeMain::setAI(bool b){
	ai = b;
	if(ai){
		player = UserDefault::getInstance()->getBoolForKey("Player");
		dif = UserDefault::getInstance()->getIntegerForKey("Difficulty",0);
	}
}
bool HorseshoeMain::getAI(){
    return ai;
}
void HorseshoeMain::playAI(){
	Piece *p1, *p2;
	if(player){
		p1 = p11;
		p2 = p12;
	} 
	else {
		p1 = p21;
		p2 = p22;
	}
	int pos1 = p1->getPos(), pos2 = p2->getPos();
	float rt = RandomHelper::random_real(0.5+((dif+1.0)/2.56),1.0+((dif+1.0)/2.56));
	if(isConnected(pos1)&&isConnected(pos2))
	{
		float rand = RandomHelper::random_real(0.0f,1.0f);
		if((pos1==1&&pos2==2)||
			(pos1==2&&pos2==1)||
			(pos1==4&&pos2==5)||
			(pos1==5&&pos2==4))
			if(rand<=0.5){
				auto seq = Sequence::create(DelayTime::create(rt),CallFunc::create(CC_CALLBACK_0(Piece::playPiece,p1)),NULL);
				p1->runAction(seq);
			}
			else{						
				auto seq = Sequence::create(DelayTime::create(rt),CallFunc::create(CC_CALLBACK_0(Piece::playPiece,p2)),NULL);
				p2->runAction(seq);
			}
		else if((pos1==1&&pos2==3)||
			(pos1==1&&pos2==4)||
			(pos1==5&&pos2==1&&empty==3)||
			(pos1==1&&pos2==5&&empty==4)||
			(pos1==2&&pos2==3)||
			(pos1==4&&pos2==2&&empty==3)||
			(pos1==2&&pos2==4&&empty==5)||
			(pos1==2&&pos2==5)||
			(pos1==3&&pos2==4)||
			(pos1==3&&pos2==5))
			if(rand<=(0.5+dif*0.35)){
				auto seq = Sequence::create(DelayTime::create(rt),CallFunc::create(CC_CALLBACK_0(Piece::playPiece,p1)),NULL);
				p1->runAction(seq);
			}
			else{						
				auto seq = Sequence::create(DelayTime::create(rt),CallFunc::create(CC_CALLBACK_0(Piece::playPiece,p2)),NULL);
				p2->runAction(seq);
			}
		else
			if(rand<=(0.5-dif*0.35)){
				auto seq = Sequence::create(DelayTime::create(rt),CallFunc::create(CC_CALLBACK_0(Piece::playPiece,p1)),NULL);
				p1->runAction(seq);
			}
			else{						
				auto seq = Sequence::create(DelayTime::create(rt),CallFunc::create(CC_CALLBACK_0(Piece::playPiece,p2)),NULL);
				p2->runAction(seq);
			}
	}
	else if(isConnected(pos1))
	{
        auto seq = Sequence::create(DelayTime::create(rt),CallFunc::create(CC_CALLBACK_0(Piece::playPiece,p1)),NULL);
        p1->runAction(seq);
	}
	else if(isConnected(pos2))
	{
        auto seq = Sequence::create(DelayTime::create(rt),CallFunc::create(CC_CALLBACK_0(Piece::playPiece,p2)),NULL);
        p2->runAction(seq);
	}
}
void HorseshoeMain::setScoreLabel(int score, Label *label){
	char buf[10];
	snprintf(buf, sizeof(buf), "%d", score);
	std::string s(buf);
	label->setString(s);
}
bool HorseshoeMain::checkEnd(bool t){
	if(t)
		if(isConnected(p21->getPos())||isConnected(p22->getPos()))
			return false;
		else{
			sred++;
			setScoreLabel(sred, redScore);
			return true;}
	else
		if(isConnected(p11->getPos())||isConnected(p12->getPos()))
			return false;
		else{
			sblu++;
			setScoreLabel(sblu, bluScore);
			return true;}
}
void HorseshoeMain::resetGame(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	empty = 3;
	p11->stopAllActions();
	p11->setScale(1);
	p11->setPos(1);
	p11->setPosition(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 + 180));
	p12->stopAllActions();
	p12->setScale(1);
	p12->setPos(5);
	p12->setPosition(Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 - 180));
	p21->stopAllActions();
	p21->setScale(1);
	p21->setPos(2);
	p21->setPosition(Vec2(origin.x + visibleSize.width/2 + 180, origin.y + 2*visibleSize.height/5 + 180));
	p22->stopAllActions();
	p22->setScale(1);
	p22->setPos(4);
	p22->setPosition(Vec2(origin.x + visibleSize.width/2 - 180, origin.y + 2*visibleSize.height/5 - 180));
	Piece::setTurn(false);
	setBGColor(Color3B(156,48,47));
	if(UserDefault::getInstance()->getBoolForKey("Sound",true)){
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/Reset.wav");
	}
	if(ai && player){
		playAI();
	}
}
void HorseshoeMain::setBGColor(Color3B col){
	auto tint = TintTo::create(0.4f,col);
	bgLayer->runAction(tint);
}
bool HorseshoeMain::isConnected(int x){
	if(x==1)
		if(empty==3||empty==4)
			return true;
		else
			return false;
	if(x==2)
		if(empty==3||empty==5)
			return true;
		else
			return false;
	if(x==3)
		return true;
	if(x==4)
		if(empty!=2)
			return true;
		else
			return false;
	if(x==5)
		if(empty!=1)
			return true;
		else
			return false;
	return false;
}