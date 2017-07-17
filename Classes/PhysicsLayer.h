#pragma once
#ifndef __PHYSICLAYER_H__
#define __PHYSICLAYER_H__

#include"cocos2d.h"
#include"onwind.h"
#include"SpriteWithPhysicsAndAnimation.h"
#include"PlaneSprite.h"
using namespace cocos2d;

class PhysicsLayer : public Layer
{
	vector<SpriteWithPhysicsAndAnimation*> m_castObject;
	void RemoveObject(SpriteWithPhysicsAndAnimation* object);

	bool CastEnemyAndBullet(int i, int j);
	bool CastToolAndPlayer(SpriteWithPhysicsAndAnimation* tool, int a, SpriteWithPhysicsAndAnimation* player);
	bool CastEnemyAndPlayer(SpriteWithPhysicsAndAnimation* a, SpriteWithPhysicsAndAnimation* b);

public:
	static Layer* createLayer();
	virtual bool init() override;
	virtual void update(float dt) override;
	CREATE_FUNC(PhysicsLayer);
	void Add(int n, ...);
	void Add(SpriteWithPhysicsAndAnimation* obj);
};

#endif // !__PHYSICLAYER_H__
