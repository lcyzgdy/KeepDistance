#include "BackgroundLayer.h"
using namespace cocos2d;

Layer * BackgroundLayer::createLayer()
{
	return BackgroundLayer::create();
}

bool BackgroundLayer::init()
{
	var cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("ui/shoot_background.plist");
	if (cache == nullptr)
	{
		m_spriteCache = nullptr;
		return false;
	}
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();

	var backgroundSprite = Sprite::createWithSpriteFrameName("background.png");
	if (backgroundSprite == nullptr)
	{
		m_backgroundSprite1 = m_backgroundSprite2 = nullptr;
		return false;
	}
	backgroundSprite->setAnchorPoint(Point::ZERO);
	backgroundSprite->setPosition(0, 0);
	backgroundSprite->getTexture()->setAntiAliasTexParameters();
	backgroundSprite->setContentSize(m_visibleSize);
	m_backgroundSprite1 = backgroundSprite;
	/*
	backgroundSprite = Sprite::createWithSpriteFrameName("background.png");
	if (backgroundSprite == nullptr)
	{
		m_backgroundSprite1 = m_backgroundSprite2 = nullptr;
		return false;
	}
	backgroundSprite->setAnchorPoint(Point::ZERO);
	backgroundSprite->setPosition(0, m_backgroundSprite1->getContentSize().height);
	backgroundSprite->getTexture()->setAntiAliasTexParameters();
	backgroundSprite->setContentSize(m_visibleSize);
	m_backgroundSprite2 = backgroundSprite;
	*/
	this->addChild(m_backgroundSprite1, 0);
	//this->addChild(m_backgroundSprite2, 0);

	//this->scheduleUpdate();
	return true;
}

void BackgroundLayer::update(float dt)
{
	/*
	m_backgroundSprite1->setPositionY(m_backgroundSprite1->getPositionY() - 0.1);
	if (m_backgroundSprite1->getPositionY() < -m_visibleSize.height + 0.55) m_backgroundSprite1->setPositionY(m_visibleSize.height - 0.56);

	m_backgroundSprite2->setPositionY(m_backgroundSprite2->getPositionY() - 0.1);
	if (m_backgroundSprite2->getPositionY() < -m_visibleSize.height + 0.55) m_backgroundSprite2->setPositionY(m_visibleSize.height - 0.56);
	*/
}
