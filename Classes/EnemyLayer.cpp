#include "EnemyLayer.h"
using namespace cocos2d;

Layer * EnemyLayer::createLayer()
{
	return EnemyLayer::create();
}

bool EnemyLayer::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();

	var cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("ui/shoot.plist");
	if (cache == nullptr)
	{
		m_frameCache = nullptr;
		return false;
	}
	m_frameCache = cache;

	randomize();
	m_smallTimeD = random(20, 50);
	m_midTimeD = random(120, 270);
	m_bigTimeD = random(180, 540);

	this->scheduleUpdate();
	return true;
}

void EnemyLayer::update(float dt)
{
	m_smallTimeD--;
	m_midTimeD--;
	m_bigTimeD--;
	if (m_smallTimeD == 0)
	{
		m_smallTimeD = random(50, 120);
		var sprite = SmallEnemySprite::createSprite("enemy1.png");

		sprite->setName("smallEnemy");
		this->addChild(sprite, 0);
		m_physicsObjects.push(dynamic_cast<SpriteWithPhysicsAndAnimation*>(sprite));
		m_scorePool.push_back(dynamic_cast<SpriteWithPhysicsAndAnimation*>(sprite));
	}
	if (m_midTimeD == 0)
	{
		m_midTimeD = random(120, 270);

		var sprite = MidEnemySprite::createSprite("enemy2.png");
		sprite->setName("midEnemy");
		this->addChild(sprite, 0);
		m_physicsObjects.push(dynamic_cast<SpriteWithPhysicsAndAnimation*>(sprite));
		m_scorePool.push_back(dynamic_cast<SpriteWithPhysicsAndAnimation*>(sprite));
	}
	if (m_bigTimeD == 0)
	{
		m_bigTimeD = random(540, 800);

		var sprite = BigEnemySprite::createSprite("enemy3_n1.png");
		sprite->setName("bigEnemy");
		this->addChild(sprite, 0);
		m_physicsObjects.push(dynamic_cast<SpriteWithPhysicsAndAnimation*>(sprite));
		m_scorePool.push_back(dynamic_cast<SpriteWithPhysicsAndAnimation*>(sprite));
	}
}