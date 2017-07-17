#pragma once
#ifndef __TOOLSPRITE_H__
#define __TOOLSPRITE_H__

#include"cocos2d.h"
#include"onwind.h"
#include"SpriteWithPhysicsAndAnimation.h"

class ToolSprite : public SpriteWithPhysicsAndAnimation
{
	float m_speed;
	bool m_jump;
public:
	static ToolSprite* create(string _name);
	static Sprite* createSprite(string _name);

	virtual bool init(string _name) override;
	virtual void update(float dt) override;
};

#endif // !__TOOLSPRITE_H__
