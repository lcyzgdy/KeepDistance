#include "PlaneSprite.h"
using namespace cocos2d;

PlaneSprite * PlaneSprite::create(string _name)
{
	var obj = new PlaneSprite();
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

Sprite * PlaneSprite::createSprite(string _name)
{
	return dynamic_cast<Sprite*>(PlaneSprite::create(_name));
}

bool PlaneSprite::init(string _name)
{
	SpriteWithPhysicsAndAnimation::init(_name);
	m_deltaTime = 300;

	var dazhaozhunbei = ParticleGalaxy::create();
	m_dazhaozhunbei = dazhaozhunbei;

	scheduleUpdate();
	return true;
}

void PlaneSprite::update(float dt)
{
	if (m_bullet > 0) m_deltaTime--;
	if (m_deltaTime == 0)
	{
		if (m_bullet > 0) m_bullet--;
		m_deltaTime = 300;
	}
	//m_particleFireworks->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
}

void PlaneSprite::ChangeBullet()
{
	m_bullet++;
}

int PlaneSprite::GetBullet()
{
	return m_bullet;
}

int PlaneSprite::GetDazhaoCount()
{
	return m_dazhaoCount;
}

void PlaneSprite::AddDazhaoCount()
{
	m_dazhaoCount++;
}

void PlaneSprite::Dazhao()
{
	if (m_dazhaoCount <= 0) return;
	m_dazhaoCount--;
	var dazhao = ParticleFireworks::create();
	dazhao->setGravity(Vec2::ZERO);
	dazhao->setPosition(this->getContentSize().width / 2, this->getContentSize().height);
	dazhao->setAngleVar(30);
	dazhao->setTotalParticles(6000);
	dazhao->setSpeed(1000);
	dazhao->setDuration(3);
	dazhao->setEmissionRate(2000);
	scheduleOnce(schedule_selector(PlaneSprite::StopDazhao), 3.0f);
	m_dazhao = dazhao;
	this->addChild(dazhao, 0);
	m_shooting = true;
}

void PlaneSprite::StopDazhao(float dt)
{
	this->removeChild(m_dazhao, true);
	m_shooting = false;
}

bool PlaneSprite::IsShooting()
{
	return m_shooting;
}

int PlaneSprite::GetTotalScore()
{
	return m_totalScore;
}

void PlaneSprite::AddTotalScore(int score)
{
	m_totalScore += score;
}
