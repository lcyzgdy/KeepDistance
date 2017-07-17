#include "SingleCastScene.h"
#include "BallPlayerLayer.h"
#include "BackgroundLayer.h"
#include "BallSprite.h"
#include "GameOverScene.h"
using namespace cocos2d;

void SingleCastScene::CreatePlayer()
{
	var player = BallSprite::createSprite("longBall.png");
	player->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
	player->setContentSize(Size(m_visibleSize.width / 10, m_visibleSize.width / 10));
	player->setName("player");
	this->addChild(player, 2);
	m_player = player;
	var listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [=](Touch* t, Event* e)
	{
		var location = t->getLocation();
		m_playerOffset = player->getPosition() - location;
		if (player->getBoundingBox().containsPoint(location))
		{
			return true;
		};
		return false;
	};
	listener->onTouchMoved = [=](Touch* t, Event* e)
	{
		//player->setPosition(t->getLocation() + m_playerOffset);
		//SyncPlayerPosition(t->getLocation().x, t->getLocation().y);

		var newPos = t->getLocation() + m_playerOffset;
		float minX = player->getContentSize().width / 2;
		float maxX = m_visibleSize.width - minX;
		float minY = player->getContentSize().height / 2;
		float maxY = m_visibleSize.height - minY;

		// Ô½½ç¼ì²â
		float x = MIN(MAX(newPos.x, minX), maxX);
		float y = MIN(MAX(newPos.y, minY), maxY);
		player->setPosition(x, y);
	};
	listener->onTouchEnded = [](Touch* t, Event* e) {};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, player);

	var circleCollider = PhysicsBody::createCircle(player->getContentSize().width / 2);
	circleCollider->getShape(0)->setRestitution(1.0f);
	circleCollider->getShape(0)->setFriction(0.0f);
	circleCollider->getShape(0)->setDensity(1.0f);
	circleCollider->setGravityEnable(false);
	circleCollider->setCategoryBitmask(0x00000f00);
	circleCollider->setCollisionBitmask(0x000000f0);
	circleCollider->setContactTestBitmask(0x00000fff);
	player->setPhysicsBody(circleCollider);

	var physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = [=](PhysicsContact& p)
	{
		if (p.getCurrentTarget()->getName().find("player") == string::npos) return true;
		if (dynamic_cast<BallSprite*>(p.getCurrentTarget())->GetWudi()) return true;
		dynamic_cast<BallSprite*>(p.getCurrentTarget())->Hit();
		scheduleOnce(schedule_selector(SingleCastScene::Jump), 2);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, player);
}


void SingleCastScene::CreateBalls()
{
	for (int i = 0; i < 6; i++)
	{
		var sprite = BallSprite::create("redBall.png");
		int x = ((random(100) & 1) == 0) ? 1 : -1;
		int y = ((random(100) & 1) == 0) ? 1 : -1;
		sprite->setPosition(random(100, (int)m_visibleSize.width - 100), random(100, (int)m_visibleSize.height - 100));
		sprite->setContentSize(Size(m_visibleSize.width / 20, m_visibleSize.width / 20));
		sprite->setName("ball");

		var circleCollider = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
		circleCollider->getShape(0)->setRestitution(1.0f);
		circleCollider->getShape(0)->setFriction(0.0f);
		circleCollider->getShape(0)->setDensity(1.0f);
		circleCollider->setGravityEnable(false);
		circleCollider->setCategoryBitmask(0x0000000f);
		circleCollider->setCollisionBitmask(0x000000ff);
		circleCollider->setContactTestBitmask(0xfffffff0);
		//Vect force = Vect(random(80000000.0f, 200000000.0f) * x, random(80000000.0f, 200000000.0f)* y);
		//circleCollider->applyForce(force);
		circleCollider->setVelocity(Vec2(random(100, 500) * x, random(100, 500) * y));
		sprite->setPhysicsBody(circleCollider);

		this->addChild(sprite, 2);
		m_balls.push_back(sprite);
	}
}

void SingleCastScene::More(float dt)
{
	for (int i = 0; i < m_balls.size(); i++)
	{
		m_balls[i]->getPhysicsBody()->setVelocity(m_balls[i]->getPhysicsBody()->getVelocity() * 1.2);
	}
	for (int i = 0; i < 3; i++)
	{
		var sprite = BallSprite::create("redBall.png");
		int x = ((random(100) & 1) == 0) ? 1 : -1;
		int y = ((random(100) & 1) == 0) ? 1 : -1;
		sprite->setPosition(random(100, (int)m_visibleSize.width - 100), random(100, (int)m_visibleSize.height - 100));
		sprite->setContentSize(Size(m_visibleSize.width / 20, m_visibleSize.width / 20));
		sprite->setName("ball");

		var circleCollider = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
		circleCollider->getShape(0)->setRestitution(1.0f);
		circleCollider->getShape(0)->setFriction(0.0f);
		circleCollider->getShape(0)->setDensity(1.0f);
		circleCollider->setGravityEnable(false);
		circleCollider->setCategoryBitmask(0x0000000f);
		circleCollider->setCollisionBitmask(0x000000ff);
		circleCollider->setContactTestBitmask(0xfffffff0);
		//Vect force = Vect(random(80000000.0f, 200000000.0f) * x, random(80000000.0f, 200000000.0f)* y);
		//circleCollider->applyForce(force);
		circleCollider->setVelocity(Vec2(random(100, 500) * x, random(100, 500) * y));
		sprite->setPhysicsBody(circleCollider);

		this->addChild(sprite, 2);
		m_balls.push_back(sprite);
	}
}

void SingleCastScene::Jump(float dt)
{
	var scene = GameOverScene::create(m_time);
	scene->setContentSize(m_visibleSize);
	var tran = TransitionRotoZoom::create(2.0f, scene);
	Director::getInstance()->replaceScene(scene);
}

Scene * SingleCastScene::createScene()
{
	return dynamic_cast<Scene*>(SingleCastScene::create());
}

Scene * SingleCastScene::createSceneWithPhysics()
{
	return dynamic_cast<Scene*>(SingleCastScene::createWithPhysics());
}

SingleCastScene * SingleCastScene::createWithPhysics()
{
	SingleCastScene *ret = new (std::nothrow) SingleCastScene();
	if (ret && ret->initWithPhysics())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
	return nullptr;
}

bool SingleCastScene::initWithPhysics()
{
	Scene::initWithPhysics();
	m_visibleSize = Director::getInstance()->getVisibleSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sucai.plist");
	randomize();
	// Background
	{
		Sprite* edgeSpace = Sprite::create("Background_start.png");
		edgeSpace->setName("wall");
		edgeSpace->setContentSize(m_visibleSize);
		PhysicsBody* boundBody = PhysicsBody::createEdgeBox(m_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
		boundBody->getShape(0)->setFriction(0.0f);
		boundBody->getShape(0)->setRestitution(1.0f);
		edgeSpace->setPhysicsBody(boundBody);
		edgeSpace->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
		this->addChild(edgeSpace, 1);
	}

	//Time
	m_time = 0;
	var timeL = Label::createWithSystemFont("0.0", "Consolas", 40);
	timeL->setColor(Color3B::BLACK);
	timeL->setPosition(m_visibleSize.width - timeL->getContentSize().width * 2,
		m_visibleSize.height - timeL->getContentSize().height * 2);
	m_timeLabel = timeL;
	this->addChild(timeL, 1, 99);

	CreatePlayer();
	CreateBalls();
	this->schedule(schedule_selector(SingleCastScene::More), 5);
	this->scheduleUpdate();
	return true;
}

void SingleCastScene::update(float dt)
{
	m_timeLabel->setString(StringUtils::format("%f", m_time));
	m_time += dt;
}


