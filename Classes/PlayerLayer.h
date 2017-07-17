#pragma once
#ifndef __PLAYERLAYER_H__
#define __PLAYERLAYER_H__

#include"cocos2d.h"
#include"onwind.h"
#include"BulletSprite.h"
#include"PlaneSprite.h"
using namespace cocos2d;

class PlayerLayer : public Layer
{
	SpriteFrameCache* m_frameCache;
	//Sprite* m_playerSprite;
	Vec2 m_playerOffset;
	bool m_shooting;
	Sprite* m_plane;
	vector<Sprite*> m_bullets;
	int m_deltaTime;

	void ShootBullet1();
	void ShootBullet2();

public:
	static Layer* createLayer();
	virtual bool init() override;
	CREATE_FUNC(PlayerLayer);
	virtual void update(float dt) override;

	queue<SpriteWithPhysicsAndAnimation*> m_physicsObjects;
	queue<SpriteWithPhysicsAndAnimation*> m_removableObjects;
};

#endif // !__PLAYERLAYER_H__