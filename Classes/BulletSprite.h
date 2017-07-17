#pragma once
#ifndef __BULLETSPRITE_H__
#define __BULLETSPRITE_H__

#include"cocos2d.h"
#include"onwind.h"
#include"SpriteWithPhysicsAndAnimation.h"

class BulletSprite : public SpriteWithPhysicsAndAnimation
{
	//bool m_canRemove;
public:
	static BulletSprite* create(string _name);
	static Sprite* createSprite(string _name);
	
	virtual void update(float dt) override;
	virtual bool init(string _name) override;
};

class BulletParticle : public cocos2d::ParticleFireworks
{
public:
	static BulletParticle* create();

	virtual bool init() override;
};

#endif // !__ROBOTSPRITE_H__
