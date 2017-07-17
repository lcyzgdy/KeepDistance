#pragma once
#ifndef __PAUSESCENE_H__
#define __PAUSESCENE_H__

#include"cocos2d.h"
#include"onwind.h"

class PauseScene : public cocos2d::Scene
{
	cocos2d::Size m_visibleSize;
	void ResumeGame(Ref* ref);

public:
	static Scene* createScene();

	virtual bool init() override;
	CREATE_FUNC(PauseScene);
};

#endif //!__PAUSESCENE_H__