#pragma once
#ifndef __ROBOTANIM_H__
#define __ROBOTANIM_H__

#include"cocos2d.h"

class RobotAnim : public cocos2d::Animation
{
public:
	RobotAnim() = default;
	~RobotAnim() = default;

	bool Init();

	Animation* GetThis();
};

#endif // !__ROBOTANIM_H__
