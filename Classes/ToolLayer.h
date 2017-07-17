#pragma once
#ifndef __TOOLLAYER_H__
#define __TOOLLAYER_H__

#include"cocos2d.h"
#include"ToolSprite.h"

class ToolLayer : public cocos2d::Layer
{
	float m_tool1DeltaT;
	float m_tool2DeltaT;
public:
	static Layer* createLayer();
	CREATE_FUNC(ToolLayer);
	virtual bool init() override;
	virtual void update(float dt) override;

	queue<SpriteWithPhysicsAndAnimation*> m_physicsObjects;
};

#endif // !__TOOLLAYER_H__
