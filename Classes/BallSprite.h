#pragma once
#ifndef __BALLSPIRTE_H__
#define __BALLSPIRTE_H__

#include"SpriteWithPhysicsAndAnimation.h"

class BallSprite : public SpriteWithPhysicsAndAnimation
{
	bool m_wudi;

	void CancelWudi(float dt);
public:
	static Sprite* createSprite(string _name);
	static BallSprite* create(string _name);
	virtual bool init(string _name);

	virtual void Hit();
	virtual void Remove();
	void Remove1(float dt);

	bool GetWudi();
};

#endif // !__BALLSPIRTE_H__
