#include "PlayerLayer.h"
using namespace cocos2d;

void PlayerLayer::ShootBullet1()
{
	var sprite = BulletSprite::createSprite("bullet1.png");
	sprite->setPosition(m_plane->getPositionX(), m_plane->getPositionY() + m_plane->getContentSize().height / 2);
	sprite->setName("bullet");
	m_bullets.push_back(sprite);
	this->addChild(sprite, 1);
	m_physicsObjects.push(dynamic_cast<SpriteWithPhysicsAndAnimation*>(sprite));
}

void PlayerLayer::ShootBullet2()
{
	var sprite = BulletSprite::createSprite("bullet2.png");
	sprite->setPosition(m_plane->getPositionX() - m_plane->getContentSize().width / 3, m_plane->getPositionY());
	sprite->setName("bullet");
	m_bullets.push_back(sprite);
	this->addChild(sprite, 1);
	m_physicsObjects.push(dynamic_cast<SpriteWithPhysicsAndAnimation*>(sprite));

	sprite = BulletSprite::createSprite("bullet2.png");
	sprite->setPosition(m_plane->getPositionX() + m_plane->getContentSize().width / 3, m_plane->getPositionY());
	sprite->setName("bullet");
	m_bullets.push_back(sprite);
	this->addChild(sprite, 1);
	m_physicsObjects.push(dynamic_cast<SpriteWithPhysicsAndAnimation*>(sprite));
}

Layer * PlayerLayer::createLayer()
{
	return dynamic_cast<Layer*>(PlayerLayer::create());
}

bool PlayerLayer::init()
{
	//m_physicsObjects = new queue<SpriteWithPhysicsAndAnimation*>();
	//m_removableObjects = new queue<SpriteWithPhysicsAndAnimation*>();
	var cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("ui/shoot.plist");
	if (cache == nullptr)
	{
		m_frameCache = nullptr;
		return false;
	}
	m_frameCache = cache;

	var player2 = PlaneSprite::createSprite("hero1.png");
	m_plane = player2;
	if (player2 == nullptr)
	{
		return false;
	}
	player2->setName("player");
	player2->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	this->addChild(player2, 0);
	m_physicsObjects.push(dynamic_cast<SpriteWithPhysicsAndAnimation*>(player2));

	var anim = Animation::create();
	anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
	anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
	anim->setDelayPerUnit(0.06);
	anim->setLoops(-1);

	var animate = Animate::create(anim);
	player2->runAction(animate);

	/*switch (CC_TARGET_PLATFORM)
	{
	case CC_PLATFORM_ANDROID:
	{*/
	var touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [=](Touch* t, Event* e)
	{
		log("Down");
		var location = t->getLocation();
		m_playerOffset = player2->getPosition() - location;
		if (player2->getBoundingBox().containsPoint(location))
		{
			return true;
		};
		return false;
	};
	touchListener->onTouchMoved = [=](Touch* t, Event* e)
	{
		log("Move");
		player2->setPosition(t->getLocation() + m_playerOffset);
	};
	touchListener->onTouchEnded = [=](Touch* t, Event* e)
	{
		log("Up");
		m_playerOffset = Vec2::ZERO;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, player2);
	/*break;
	}
	case (CC_PLATFORM_WIN32 || CC_PLATFORM_LINUX):
	{
		var mouseListener = EventListenerMouse::create();
		mouseListener->onMouseDown = [=](Event* e)
		{
			log("down");
			m_shooting = true;
		};
		mouseListener->onMouseMove = [=](Event* e)
		{
			var location = dynamic_cast<EventMouse*>(e)->getLocationInView();
			player2->setPosition(location);
		};
		mouseListener->onMouseUp = [=](Event* e)
		{
			m_playerOffset = Vec2::ZERO;
			m_shooting = false;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, player2);
		break;
	}
	default:
		break;
	}*/

	this->scheduleUpdate();
	return true;
}

void PlayerLayer::update(float dt)
{
	m_deltaTime++;
	if (false || m_deltaTime < 5) return;
	//ShootBullet1();
	if (dynamic_cast<PlaneSprite*>(m_plane)->GetBullet() == 0) ShootBullet1();
	else ShootBullet2();

	m_deltaTime = 0;
}
