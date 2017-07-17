#include "EnemySprite.h"
using namespace cocos2d;

EnemySprite * EnemySprite::create(string _name)
{
	var obj = new EnemySprite();
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
	};
}

Sprite * EnemySprite::createSprite(string _name)
{
	return dynamic_cast<Sprite*>(EnemySprite::create(_name));
}

bool EnemySprite::init(string _name)
{
	SpriteWithPhysicsAndAnimation::init(_name);
	this->setPositionY(Director::getInstance()->getVisibleSize().height);
	this->setPositionX(random(static_cast<int>(getContentSize().width / 2), static_cast<int>(Director::getInstance()->getVisibleSize().width - getContentSize().width / 2)));
	CreateAnimation();
	m_speed = 0.5f;
	scheduleUpdate();
	return true;
}

void EnemySprite::update(float dt)
{
	setPositionY(getPositionY() - m_speed);
	if (getPositionY() < -10)
	{
		SetCanRemove();
	}
}

void EnemySprite::Remove()
{
	//if (!m_canRemove) return;
	this->unscheduleUpdate();
	this->stopAllActions();
	var animation = m_downAnim;
	var animate = Animate::create(animation);
	var act = CallFunc::create([=]()
	{
		this->removeFromParentAndCleanup(true);
		//this->autorelease();
	});
	var sq = Sequence::create(animate, act, nullptr);
	this->runAction(sq);
}

void EnemySprite::CreateAnimation()
{
}

void EnemySprite::Hit()
{
	SpriteWithPhysicsAndAnimation::Hit();
	var hitAnim = m_hitAnim;
	if (hitAnim == nullptr) return;
	this->stopAllActions();
	var animate = Animate::create(hitAnim);
	var act = CallFunc::create([=]()
	{
		this->stopAllActions();
		if (m_flyAnim == nullptr)
		{
			this->stopAllActions();
			return;
		}
		var fly = Animate::create(m_flyAnim);
		this->runAction(fly);
	});
	var sq = Sequence::create(animate, act, nullptr);
	this->runAction(sq);
}
