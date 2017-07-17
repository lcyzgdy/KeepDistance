#pragma once
#ifndef __BACKGROUNDEND_H__
#define __BACKGROUNDEND_H__

#include"cocos2d.h"
using namespace cocos2d;

class Background_end:public Layer
{
public:
	Background_end();
	static Background_end* create();
	bool init();
};

#endif //! __BACKGROUNDEND_H__