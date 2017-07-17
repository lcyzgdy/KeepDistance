#pragma once
#ifndef __ENEMYSPRITE_H__
#define __ENEMYSPRITE_H__

#include"SpriteWithPhysicsAndAnimation.h"

class EnemySprite : public SpriteWithPhysicsAndAnimation
{
	bool m_shooting;
	int m_deltaTime;
protected:
	float m_speed;
	cocos2d::Animation* m_flyAnim, *m_downAnim, *m_hitAnim;
public:
	static EnemySprite* create(string _name);
	static Sprite* createSprite(string _name);

	virtual bool init(string _name) override;
	virtual void update(float dt) override;
	virtual void Remove() override;
	virtual void CreateAnimation() override;
	virtual void Hit() override;
};


#endif