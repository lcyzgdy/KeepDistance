#pragma once
#ifndef __ENEMYLAYER_H__
#define __ENEMYLAYER_H__

#include"cocos2d.h"
#include"onwind.h"
#include"EnemyPlaneSprite.h"
using namespace cocos2d;

class EnemyLayer : public Layer
{
	SpriteFrameCache* m_frameCache;
	int m_smallTimeD;
	int m_midTimeD;
	int m_bigTimeD;
	Size m_visibleSize;
	Vec2 m_origin;

public:
	static Layer* createLayer();
	virtual bool init() override;
	CREATE_FUNC(EnemyLayer);
	virtual void update(float dt) override;

	queue<SpriteWithPhysicsAndAnimation*> m_physicsObjects;
	vector<SpriteWithPhysicsAndAnimation*> m_scorePool;

	struct CmpS
	{
		bool operator()(SpriteWithPhysicsAndAnimation* a, SpriteWithPhysicsAndAnimation* b)
		{
			if (a->CanRemove() == true && b->CanRemove() == false) return true;
			//if (a->CanRemove() == false && b->CanRemove() == true) return false;
			return false;
		}
	};
};

#endif // !__ENEMYLAYER_H__
