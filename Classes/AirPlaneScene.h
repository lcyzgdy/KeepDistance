#pragma once
#ifndef __ROBOTSCENE_H__
#define __ROBOTSCENE_H__

#include "cocos2d.h"
#include "PlayerLayer.h"
#include "BackgroundLayer.h"
#include "EnemyLayer.h"
#include "PhysicsLayer.h"
#include "UILayer.h"
#include "ToolLayer.h"
#include "onwind.h"

class AirPlaneScene : public cocos2d::Scene
{
	cocos2d::Size m_visibleSize;
	PlayerLayer* m_player;
	EnemyLayer* m_enemy;
	PhysicsLayer* m_physics;
	UILayer* m_ui;
	ToolLayer* m_tool;

	vector<Sprite*> m_castObject;

public:
	static Scene* createScene();

	virtual bool init() override;
	virtual void update(float dt) override;
	CREATE_FUNC(AirPlaneScene);

	void AddDazhaoCount();
};

#endif // !__ROBOTSCENE_H__
