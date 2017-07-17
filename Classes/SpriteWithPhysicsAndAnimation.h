#pragma once
#ifndef __SPRITEWITHPHYSICANDANIMATION_H__
#define __SPRITEWITHPHYSICANDANIMATION_H__

#include"cocos2d.h"
#include"onwind.h"

class SpriteWithPhysicsAndAnimation : public cocos2d::Sprite
{
protected:
	bool m_canRemove;
	bool m_died;
	int m_hp;
	int m_score;

public:
	static Sprite* createSprite(string _name);
	static SpriteWithPhysicsAndAnimation* create(string _name);
	virtual bool init(string _name);

	void SetCanRemove();
	bool CanRemove();
	bool Died();
	virtual void Hit();
	virtual void Remove();
	virtual void CreateAnimation();
	int GetScore();
};


bool Cmp(SpriteWithPhysicsAndAnimation* a, SpriteWithPhysicsAndAnimation* b);

#endif // !__SPRITEWITHPHYSICANDANIMATION_H__
