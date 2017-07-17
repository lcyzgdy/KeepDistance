#include "ToolSprite.h"
using namespace cocos2d;

ToolSprite * ToolSprite::create(string _name)
{
	var obj = new ToolSprite();
	if (obj && obj->init(_name))
	{
		obj->autorelease();
		return obj;
	}
	else
	{
		delete obj;
		obj = nullptr;
		return nullptr;
	};
}

Sprite * ToolSprite::createSprite(string _name)
{
	return dynamic_cast<Sprite*>(ToolSprite::create(_name));
}

bool ToolSprite::init(string _name)
{
	SpriteWithPhysicsAndAnimation::init(_name);
	m_speed = 1.0f;
	scheduleUpdate();
	return true;
}

void ToolSprite::update(float dt)
{
	setPositionY(getPositionY() - m_speed);
	if (getPositionY() < Director::getInstance()->getVisibleSize().height / 2 - 40 && !m_jump)
	{
		m_jump = true;
		m_speed = -m_speed - 0.86;
	}
	if (getPositionY() > Director::getInstance()->getVisibleSize().height / 2 + 40 && m_jump)
	{
		m_speed = -m_speed;// +0.86;
	}
	if (getPositionY() < -10)
	{
		SetCanRemove();
	}
}
