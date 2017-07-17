#pragma once
#ifndef __BACKGROUNDSPRITE_H__
#define __BACKGROUNDSPRITE_H__

#include"cocos2d.h"
#include"onwind.h"

class BackGroundSprite : public cocos2d::Sprite
{
	//Vec2 m_playerOffset;
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_origin;
public:
	static Sprite* createSprite();
	virtual bool init() override;
	CREATE_FUNC(BackGroundSprite);
	virtual void update(float dt) override;
};

#endif // !__BACKGROUNDSPRITE_H__
