#include "Background.h"
using namespace cocos2d;

Background::Background()
{
}

Background* Background::create()
{
	Background* background = new Background();
	if(background && background->init())
	{
		background->autorelease();
		return background;
	}
	else
	{
		delete background;
		background = nullptr;
		return nullptr;
	}
}
bool Background::init()
{
	 if ( !Layer::init() )
    {
        return false;
    }
	//Ìí¼Ó±³¾°Í¼Æ¬
	auto background = Sprite::create("Background/Background_start.png");
	background->setContentSize(Director::getInstance()->getVisibleSize());
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(0,0);
	this->addChild(background);

	return true;
}
