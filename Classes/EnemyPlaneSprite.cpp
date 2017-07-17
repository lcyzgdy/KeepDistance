#include "EnemyPlaneSprite.h"
using namespace cocos2d;

SmallEnemySprite * SmallEnemySprite::create(string _name)
{
	var obj = new SmallEnemySprite();
	if (obj && obj->init(_name))
	{
		//obj->autorelease();
		return obj;
	}
	else
	{
		delete obj;
		obj = nullptr;
		return nullptr;
	}
}

Sprite * SmallEnemySprite::createSprite(string _name)
{
	return dynamic_cast<Sprite*>(SmallEnemySprite::create(_name));
}

void SmallEnemySprite::CreateAnimation()
{
	m_downAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Down");
	if (m_downAnim == nullptr)
	{
		var downAnim = Animation::create();
		for (int i = 1; i <= 4; i++)
		{
			var png = StringUtils::format("enemy1_down%d.png", i);
			downAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
		}
		downAnim->setDelayPerUnit(0.07f);
		downAnim->setLoops(1);
		AnimationCache::getInstance()->addAnimation(downAnim, string(typeid(this).name()) + "Down");
		m_downAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Down");
	}
}

bool SmallEnemySprite::init(string _name)
{
	EnemySprite::init(_name);
	m_score = 1;
	return true;
}
/*
void SmallEnemySprite::Remove()
{
	EnemySprite::Remove();
	if (!m_canRemove) return;
	this->unscheduleUpdate();
	var animation = m_downAnim;
	var animate = Animate::create(animation);
	var act = CallFunc::create([=]()
	{
		this->removeFromParentAndCleanup(true);
		this->autorelease();
	});
	var sq = Sequence::create(animate, act, nullptr);
	this->runAction(sq);
}*/

MidEnemySprite * MidEnemySprite::create(string _name)
{
	var obj = new MidEnemySprite();
	if (obj && obj->init(_name))
	{
		//obj->autorelease();
		return obj;
	}
	else
	{
		delete obj;
		obj = nullptr;
		return nullptr;
	};
}

Sprite * MidEnemySprite::createSprite(string _name)
{
	return dynamic_cast<Sprite*>(MidEnemySprite::create(_name));
}

void MidEnemySprite::CreateAnimation()
{
	m_downAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Down");
	if (m_downAnim == nullptr)
	{
		var downAnim = Animation::create();
		for (int i = 1; i <= 4; i++)
		{
			var png = StringUtils::format("enemy2_down%d.png", i);
			downAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
		}
		downAnim->setDelayPerUnit(0.07f);
		downAnim->setLoops(1);
		AnimationCache::getInstance()->addAnimation(downAnim, string(typeid(this).name()) + "Down");
		m_downAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Down");
	}

	m_hitAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Hit");
	if (m_hitAnim == nullptr)
	{
		var hitAnim = Animation::create();
		hitAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
		hitAnim->setDelayPerUnit(0.02f);
		hitAnim->setLoops(1);
		AnimationCache::getInstance()->addAnimation(hitAnim, string(typeid(this).name()) + "Hit");
		m_hitAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Hit");
	}

	m_flyAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Fly");
	if (m_flyAnim == nullptr)
	{
		var flyAnim = Animation::create();
		flyAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png"));
		flyAnim->setDelayPerUnit(0.02f);
		flyAnim->setLoops(-1);
		AnimationCache::getInstance()->addAnimation(flyAnim, string(typeid(this).name()) + "Fly");
		m_flyAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Fly");
	}
}

bool MidEnemySprite::init(string _name)
{
	EnemySprite::init(_name);
	m_hp = 10;
	m_speed = 0.3;
	m_score = 3;
	return true;
}
/*
void MidEnemySprite::Remove()
{
	if (!m_canRemove) return;
	this->unscheduleUpdate();
	var animation = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Down");
	var animate = Animate::create(animation);
	var act = CallFunc::create([=]()
	{
		this->removeFromParentAndCleanup(true);
		this->autorelease();
	});
	var sq = Sequence::create(animate, act, nullptr);
	//sq->setTag(13);
	this->runAction(sq);
}*/

BigEnemySprite * BigEnemySprite::create(string _name)
{
	var obj = new BigEnemySprite();
	if (obj && obj->init(_name))
	{
		//obj->autorelease();
		return obj;
	}
	else
	{
		delete obj;
		obj = nullptr;
		return nullptr;
	};
}

Sprite * BigEnemySprite::createSprite(string _name)
{
	return dynamic_cast<Sprite*>(BigEnemySprite::create(_name));
}

void BigEnemySprite::CreateAnimation()
{
	m_downAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Down");
	if (m_downAnim == nullptr)
	{
		var downAnim = Animation::create();
		for (int i = 1; i <= 6; i++)
		{
			var png = StringUtils::format("enemy3_down%d.png", i);
			downAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
		}
		downAnim->setDelayPerUnit(0.07f);
		downAnim->setLoops(1);
		AnimationCache::getInstance()->addAnimation(downAnim, string(typeid(this).name()) + "Down");
		m_downAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Down");
	}

	m_hitAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Hit");
	if (m_hitAnim == nullptr)
	{
		var hitAnim = Animation::create();
		hitAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_hit.png"));
		hitAnim->setDelayPerUnit(0.01f);
		hitAnim->setLoops(1);
		AnimationCache::getInstance()->addAnimation(hitAnim, string(typeid(this).name()) + "Hit");
		m_hitAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Hit");
	}

	m_flyAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Fly");
	if (m_flyAnim == nullptr)
	{
		var flyAnim = Animation::create();
		for (int i = 1; i <= 2; i++)
		{
			var png = StringUtils::format("enemy3_n%d.png", i);
			flyAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
		}
		flyAnim->setDelayPerUnit(0.02f);
		flyAnim->setLoops(-1);
		AnimationCache::getInstance()->addAnimation(flyAnim, string(typeid(this).name()) + "Fly");
		m_flyAnim = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Fly");
	}
}

bool BigEnemySprite::init(string _name)
{
	EnemySprite::init(_name);

	//var animation = m_flyAnim;
	//var animate = Animate::create(animation);
	var animate = Animate::create(m_flyAnim);
	animate->setTag(14);
	this->runAction(animate);

	m_hp = 50;
	m_speed = 0.15;
	m_score = 6;
	return true;
}
/*
void BigEnemySprite::Remove()
{
	if (!m_canRemove) return;
	this->unscheduleUpdate();
	this->stopActionByTag(14);
	var animation = AnimationCache::getInstance()->getAnimation(string(typeid(this).name()) + "Down");
	var animate = Animate::create(animation);
	var act = CallFunc::create([=]()
	{
		this->removeFromParentAndCleanup(true);
		this->autorelease();
	});
	var sq = Sequence::create(animate, act, nullptr);
	this->runAction(sq);
}
*/