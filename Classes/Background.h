#pragma once
#include"cocos2d.h"
using namespace cocos2d;


class Background:public Layer
{
public:
	Background();
	static Background* create();
	bool init();

};