#pragma once
#ifndef __UILAYER_H__
#define __UILAYER_H__

#include"cocos2d.h"
#include"PlaneSprite.h"
#include"onwind.h"

class UILayer : public cocos2d::Layer
{
	cocos2d::Label* m_labelScore;
	cocos2d::Label* m_labelDazhaoCount;
	int m_score;
	int m_dazhaoCount;
	cocos2d::Size m_visibleSize;
	void Dazhao(Ref * ref);
	void PauseGame(Ref* ref);

public:
	static Layer* createLayer();
	virtual bool init() override;
	CREATE_FUNC(UILayer);
	virtual void update(float dt) override;

	void AddScore(int score);
	void SetDazhaoCount(int h);
};

#endif // !__UILAYER_H__
