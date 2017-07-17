#pragma once
#ifndef __CLOSINGITEM_H__
#define __CLOSINGITEM_H__

#include"cocos2d.h"
using namespace cocos2d;

class Closing_item :public Layer
{
public:
	Closing_item();
	static Closing_item* create(float t);
	bool init(float t);
};

#endif // !__CLOSINGITEM_H__