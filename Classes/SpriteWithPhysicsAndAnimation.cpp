#include "SpriteWithPhysicsAndAnimation.h"
using namespace cocos2d;

Sprite * SpriteWithPhysicsAndAnimation::createSprite(string _name)
{
	return SpriteWithPhysicsAndAnimation::create(_name);
}

SpriteWithPhysicsAndAnimation* SpriteWithPhysicsAndAnimation::create(string _name)
{
	var obj = new SpriteWithPhysicsAndAnimation();
	if (obj && obj->init(_name))
	{
		obj->autorelease();
		return obj;
	}
	else
	{
		delete obj;
		obj = nullptr;
		return nullptr;
	}
}

bool SpriteWithPhysicsAndAnimation::init(string _name)
{
	if (!initWithSpriteFrameName(_name))
	{
		initWithFile(_name);
	}
	m_hp = 1;
	return true;
}

void SpriteWithPhysicsAndAnimation::SetCanRemove()
{
	m_canRemove = true;
}

bool SpriteWithPhysicsAndAnimation::CanRemove()
{
	return m_canRemove;
}

bool SpriteWithPhysicsAndAnimation::Died()
{
	return m_died;
}

void SpriteWithPhysicsAndAnimation::Hit()
{
	m_hp--;
	if (m_hp <= 0) m_died = true;
}

void SpriteWithPhysicsAndAnimation::Remove()
{
	this->removeFromParentAndCleanup(true);
	//this->autorelease();
}

void SpriteWithPhysicsAndAnimation::CreateAnimation()
{
}

int SpriteWithPhysicsAndAnimation::GetScore()
{
	return m_score;
}

bool Cmp(SpriteWithPhysicsAndAnimation * a, SpriteWithPhysicsAndAnimation * b)
{
	if (a->Died() == true && b->Died() == false) return true;
	return false;
}
