#include "BackgroundSprite.h"
using namespace cocos2d;

Sprite * BackGroundSprite::createSprite()
{
	return Sprite::create("ui/shoot_background.plist");
}

bool BackGroundSprite::init()
{
	scheduleUpdate();
	return true;
}

void BackGroundSprite::update(float dt)
{
	this->setPositionY(this->getPositionY() - 0.05);
	if (this->getPositionY() < -m_visibleSize.height + 0.55) this->setPositionY(m_visibleSize.height - 0.56);
}

