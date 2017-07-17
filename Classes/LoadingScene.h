#pragma once
#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include"cocos2d.h"
#include"onwind.h"

class LoadingScene : public cocos2d::Scene
{
public:
	static Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(LoadingScene);
};

#endif // !__LOADINGSCENE_H__
