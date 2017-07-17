#pragma once
#ifndef __BACKGROUNDLAERR_H__
#define __BACKGROUNDLAYER_H__

#include"cocos2d.h"
#include"BackgroundSprite.h"
#include"onwind.h"

class BackgroundLayer : public cocos2d::Layer
{
	cocos2d::SpriteFrameCache* m_spriteCache;
	cocos2d::Sprite* m_backgroundSprite1;
	cocos2d::Sprite* m_backgroundSprite2;
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_origin;

public:
	static Layer* createLayer();
	virtual bool init() override;
	CREATE_FUNC(BackgroundLayer);
	virtual void update(float dt) override;
};

#endif // !__BACKGROUNDSCENE_H__
