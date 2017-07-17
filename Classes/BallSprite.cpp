#include "BallSprite.h"
using namespace cocos2d;

void BallSprite::CancelWudi(float dt)
{
	//m_wudi = false;
}

Sprite * BallSprite::createSprite(string _name)
{
	return BallSprite::create(_name);
}

BallSprite * BallSprite::create(string _name)
{
	var obj = new BallSprite();
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

bool BallSprite::init(string _name)
{
	SpriteWithPhysicsAndAnimation::init(_name);
	m_wudi = true;
	scheduleOnce(schedule_selector(BallSprite::CancelWudi), 10);
	return true;
}

void BallSprite::Hit()
{
	if (m_wudi) return;
	if (this->getName().find("player") != string::npos)
	{
		var emitter = ParticleFlower::createWithTotalParticles(5000);
		emitter->setSpeed(1500);
		emitter->setGravity(Point::ZERO);
		emitter->setDuration(0.25);
		emitter->isAutoRemoveOnFinish();
		emitter->setPosition(this->getPositionX(), this->getPositionY());
		emitter->setName("explotion");
		this->getParent()->addChild(emitter, 10);
		this->scheduleOnce(schedule_selector(BallSprite::Remove1), 0.5);
		this->removeFromParent();
	}
}

void BallSprite::Remove()
{
	this->removeFromParentAndCleanup(true);
}

void BallSprite::Remove1(float dt)
{
	//this->removeChildByName("explotion");

	//this->removeFromParentAndCleanup(true);
}

bool BallSprite::GetWudi()
{
	return m_wudi;
}
