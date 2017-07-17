#pragma once

#ifndef __SWITCHITEM_H__
#define __SWITCHITEM_H__

#include"cocos2d.h"
using namespace cocos2d;

class Switch_item :public Layer
{
public:
	Switch_item();
	static Switch_item* create();
	bool init();
};

#endif