#pragma once
#ifndef __BALLPLAYERLAYER_H__
#define __BALLPLAYERLAYER_H__

#include"BallSprite.h"
#include"cocos2d.h"
using namespace cocos2d;

class BallPlayerLayer : public Layer
{
	Vec2 m_playerOffset;
public:
	static Layer* createLayer();
	virtual bool init() override;
	CREATE_FUNC(BallPlayerLayer);
	virtual void update(float dt) override;
};

#endif // !__BALLPLAYERLAYER_H__
