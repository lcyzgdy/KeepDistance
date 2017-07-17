#include "BulletSprite.h"
using namespace cocos2d;

BulletSprite* BulletSprite::create(string _name)
{
	var bullet = new BulletSprite();
	if (bullet && bullet->init(_name))
	{
		//m_bullet->autorelease();
		return bullet;
	}
	else
	{
		delete bullet;
		bullet = nullptr;
		return nullptr;
	}
}

Sprite * BulletSprite::createSprite(string _name)
{
	return dynamic_cast<Sprite*>(BulletSprite::create(_name));
}

void BulletSprite::update(float dt)
{
	if (this->getPositionY() > Director::getInstance()->getVisibleSize().height)
	{
		this->SetCanRemove();
		return;
	}
	this->setPositionY(this->getPositionY() + 5);
}

bool BulletSprite::init(string _name)
{
	if (!SpriteWithPhysicsAndAnimation::init(_name))
	{
		return false;
	}
	scheduleUpdate();
	return true;
}







BulletParticle * BulletParticle::create()
{
	BulletParticle* obj = new (std::nothrow) BulletParticle();
	if (obj && obj->init())
	{
		obj->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(obj);
	}
	return obj;
}

bool BulletParticle::init()
{
	ParticleFireworks::init();
	this->setGravity(Vec2::ZERO);
	//this->
	return true;
}


