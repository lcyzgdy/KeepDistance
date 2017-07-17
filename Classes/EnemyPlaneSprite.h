#pragma once
#ifndef __ENEMYPLANESPRITE_H__
#define __ENEMYPLANESPRITE_H__

#include "EnemySprite.h"

class SmallEnemySprite : public EnemySprite
{
public:
	static SmallEnemySprite* create(string _name);
	static Sprite* createSprite(string _name);
	virtual void CreateAnimation() override;
	virtual bool init(string _name) override;
	//virtual void Remove() override;
};

class MidEnemySprite : public EnemySprite
{
public:
	static MidEnemySprite* create(string _name);
	static Sprite* createSprite(string _name);
	virtual void CreateAnimation() override;
	virtual bool init(string _name) override;
	//virtual void Remove() override;
};

class BigEnemySprite : public EnemySprite
{
public:
	static BigEnemySprite* create(string _name);
	static Sprite* createSprite(string _name);
	virtual void CreateAnimation() override;
	virtual bool init(string _name) override;
	//virtual void Remove() override;
};

#endif // !__ENEMYPLANESPRITE_H__
