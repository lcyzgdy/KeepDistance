#pragma once
#ifndef __SINGLECASTSCENE_H__
#define __SINGLECASTSCENE_H__

#include"cocos2d.h"
#include"onwind.h"
#include"SpriteWithPhysicsAndAnimation.h"
using namespace cocos2d;

class SingleCastScene : public cocos2d::Scene
{
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_playerOffset;
	cocos2d::Sprite* m_player;
	string m_key;
	vector<Sprite*> m_balls;

	float m_time;
	cocos2d::Label* m_timeLabel;

	void CreatePlayer();
	void CreateBalls();
	void More(float dt);
	void Jump(float dt);

public:
	static cocos2d::Scene* createScene();
	static cocos2d::Scene* createSceneWithPhysics();
	static SingleCastScene* createWithPhysics();
	CREATE_FUNC(SingleCastScene);
	virtual bool initWithPhysics() override;
	virtual void update(float dt) override;
};


#endif // !__SINGLECASTSCENE_H__
