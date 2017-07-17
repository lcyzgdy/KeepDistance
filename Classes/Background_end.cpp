#include "Background_end.h"
using namespace cocos2d;

Background_end::Background_end()
{}

Background_end* Background_end::create()
{
	Background_end* background_end = new Background_end();
	if(background_end && background_end->init())
	{
		background_end->autorelease();
		return background_end;
	}
	else
	{
		delete background_end;
		background_end = nullptr;
		return nullptr;
	}

}

bool Background_end::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
	//Ìí¼Ó±³¾°Í¼Æ¬
	auto background_end = Sprite::create("Background_end.png");
	background_end->setContentSize(this->getContentSize());
	background_end->setAnchorPoint(Point::ZERO);
	background_end->setPosition(0,0);
	this->addChild(background_end);

	return true;

}