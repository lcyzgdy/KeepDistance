#pragma once
#ifndef __OTHERBALLLAYER_H__
#define __OTHERBALLLAYER_H__

#include"BallSprite.h"
#include"cocos2d.h"
using namespace cocos2d;

class OtherBallLayer : public Layer
{
	Size m_visibleSize;
public:
	static Layer* createLayer();
	virtual bool init() override;
	CREATE_FUNC(OtherBallLayer);
	virtual void update(float dt) override;
};

#endif // !__OTHERBALLLAYER_H__
