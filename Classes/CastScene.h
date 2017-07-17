#pragma once
#ifndef __CAST_H__
#define __CAST_H__

#include"cocos2d.h"
#include"onwind.h"
#include"SpriteWithPhysicsAndAnimation.h"
#include "NetworkLayer.h"

class CastScene : public cocos2d::Scene
{
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_playerOffset;
	cocos2d::Sprite* m_player;
	NetworkLayer* m_net;
	string m_key;
	map<string, Sprite*> m_other;
	vector<Sprite*> m_balls;

	float m_time;
	cocos2d::Label* m_timeLabel;

	bool m_died;

	void SyncPlayerPosition(float dt);
	void SyncBallPosition(float dt);
	void SyncBallPositionFromServer(float dt);

	void CreatePlayer();
	void CreateBalls();
	void Jump(float dt);


public:
	static cocos2d::Scene* createScene();
	static cocos2d::Scene* createSceneWithPhysics();
	static CastScene* createWithPhysics();
	CREATE_FUNC(CastScene);
	virtual bool init() override;
	virtual bool initWithPhysics() override;
	virtual void update(float dt) override;
};

#endif // !__CAST_H__
