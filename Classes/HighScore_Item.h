#pragma
#include"cocos2d.h"
using namespace cocos2d;

class HighScore_item:public Layer
{
public:
	HighScore_item();
	static HighScore_item* create();
	bool init();
};