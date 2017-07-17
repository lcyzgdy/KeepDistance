#pragma once
#ifndef __PLANESPRITE_H__
#define __PLANESPRITE_H__

#include"cocos2d.h"
#include"SpriteWithPhysicsAndAnimation.h"
#include"onwind.h"

class PlaneSprite : public SpriteWithPhysicsAndAnimation
{
	bool m_shooting;
	int m_deltaTime;
	int m_bullet;
	int m_dazhaoCount;
	int m_totalScore;
	cocos2d::ParticleGalaxy* m_dazhaozhunbei;
	cocos2d::ParticleFireworks* m_dazhao;

public:
	static PlaneSprite* create(string _name);
	static Sprite* createSprite(string _name);

	virtual bool init(string _name) override;
	virtual void update(float dt) override;

	void ChangeBullet();
	int GetBullet();
	int GetDazhaoCount();
	void AddDazhaoCount();
	void Dazhao();
	void StopDazhao(float dt);
	bool IsShooting();
	int GetTotalScore();
	void AddTotalScore(int score);
};

#endif