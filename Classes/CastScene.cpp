#include "CastScene.h"
#include "BallPlayerLayer.h"
#include "BackgroundLayer.h"
#include "BallSprite.h"
#include "GameOverScene.h"
using namespace cocos2d;

void CastScene::CreatePlayer()
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
		m_net->SendImmediate(UpdateData::UpdatePlayerPositionAndState(p.getCurrentTarget()->getPosition(), STATE::DIED));
		dynamic_cast<BallSprite*>(p.getCurrentTarget())->Hit();
		scheduleOnce(schedule_selector(CastScene::Jump), 2);
		m_died = true;
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, player);
}


void CastScene::CreateBalls()
{
	for (int i = 0; i < 3; i++)
	{
		var sprite = BallSprite::create("redBall.png");
		int x = (random(100) & 1) == 0 ? 1 : -1;
		int y = (random(100) & 1) == 0 ? 1 : -1;
		sprite->setPosition(random(100, (int)m_visibleSize.width) - 100, random(100, (int)m_visibleSize.height - 100));
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
		//Vect force = Vect(random(200000000.0f, 400000000.0f) * x, random(200000000.0f, 400000000.0f)* y);
		//circleCollider->applyForce(force);
		circleCollider->setVelocity(Vec2(random(100, 500) * x, random(100, 500) * y));
		sprite->setPhysicsBody(circleCollider);

		this->addChild(sprite, 2);
		m_balls.push_back(sprite);
	}
}

void CastScene::Jump(float dt)
{
	var scene = GameOverScene::create(m_time);
	scene->setContentSize(m_visibleSize);
	var tran = TransitionRotoZoom::create(2.0f, scene);
	this->removeAllChildrenWithCleanup(true);
	Director::getInstance()->replaceScene(scene);
}

Scene * CastScene::createScene()
{
	return dynamic_cast<Scene*>(CastScene::create());
}

Scene * CastScene::createSceneWithPhysics()
{
	return dynamic_cast<Scene*>(CastScene::createWithPhysics());
}

CastScene * CastScene::createWithPhysics()
{
	CastScene *ret = new (std::nothrow) CastScene();
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

bool CastScene::init()
{
	return true;
}

bool CastScene::initWithPhysics()
{
	Scene::initWithPhysics();
	m_visibleSize = Director::getInstance()->getVisibleSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sucai.plist");
	randomize();
	// Background
	{
		Sprite* edgeSpace = Sprite::create("brown.png");
		edgeSpace->setName("wall");
		edgeSpace->setContentSize(m_visibleSize);
		PhysicsBody* boundBody = PhysicsBody::createEdgeBox(m_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
		boundBody->getShape(0)->setFriction(0.0f);
		boundBody->getShape(0)->setRestitution(1.0f);
		edgeSpace->setPhysicsBody(boundBody);
		edgeSpace->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
		this->addChild(edgeSpace, 1);
	}
	// Net
	{
		var net = NetworkLayer::createLayer();
		net->setPosition(Vec2::ZERO);
		this->addChild(net, 0);
		m_net = dynamic_cast<NetworkLayer*>(net);
	}
	//Time
	m_time = 0;
	var timeL = Label::createWithSystemFont("0.0", "Consolas", 40);
	timeL->setColor(Color3B::BLACK);
	timeL->setPosition(m_visibleSize.width - timeL->getContentSize().width * 2,
		m_visibleSize.height - timeL->getContentSize().height * 2);
	m_timeLabel = timeL;
	this->addChild(timeL, 1, 99);

	this->scheduleUpdate();
	this->schedule(schedule_selector(CastScene::SyncPlayerPosition), 0.005, -1, 0);
	//this->schedule(schedule_selector(CastScene::SyncPlayerPosition), 0, 1, 0);
	return true;
}

void CastScene::update(float dt)
{
	if (m_died) return;
	m_timeLabel->setString(StringUtils::format("%f", m_time));
	m_time += dt;

	if (m_net->Updated())
	{
		string jsonStr = m_net->GetData();
		Document d;
		d.Parse<rapidjson::kParseDefaultFlags>(jsonStr.c_str());
		if (d.HasParseError()) return;
		if (d.IsObject())
		{
			COMMAND com = (COMMAND)d["COMMAND"].GetInt();
			switch (com)
			{
			case INIT:
			{
				m_key = d["KEY"].GetString();
				CreatePlayer();
				CreateBalls();
				m_net->SafeImportant();
				this->schedule(schedule_selector(CastScene::SyncBallPosition), 1, -1, 0);
				break;
			}
			case NF:
			{
				CreatePlayer();
				m_key = d["KEY"].GetString();
				m_net->SafeImportant();
				this->schedule(schedule_selector(CastScene::SyncBallPositionFromServer), 1, 1, 0);
				break;
			}
			default:
				break;
			}
		}
	}

	if (m_net->OpUpdated())
	{
		string jsonStr = m_net->GetOpData();
		Document d;
		d.Parse<rapidjson::kParseDefaultFlags>(jsonStr.c_str());
		if (d.HasParseError()) return;
		if (d.IsObject())
		{
			COMMAND com = (COMMAND)d["COMMAND"].GetInt();
			if (com == COMMAND::OP)
			{
				Vec2 pos;
				STATE state;
				string key;
				UpdateData::GetPlayerPositionAndState(d, pos, state, key);
				switch (state)
				{
				case LIVE:
				{
					if (m_other.find(key) != m_other.end())
					{
						m_other[key]->setPosition(pos);
					}
					else
					{
						var sprite = BallSprite::createSprite("longBall.png");
						sprite->setPosition(pos);
						sprite->setContentSize(Size(m_visibleSize.width / 10, m_visibleSize.width / 10));
						sprite->setName("other");
						this->addChild(sprite, 2);
						m_other[key] = sprite;
					}
					break;
				}
				case DIED:
				{
					if (m_other.find(key) != m_other.end())
					{
						m_other[key]->removeFromParentAndCleanup(true);
						m_other.erase(key);
					}
					break;
				}
				case WIN:
				{
					// Load Win Scene
					break;
				}
				case LOST:
				{
					// Load Lost Scene
					break;
				}
				default:
					break;
				}
			}
		}
	}
}


void CastScene::SyncPlayerPosition(float dt)
{
	if (m_died) return;
	if (m_player == nullptr) return;
	m_net->SendImmediate(UpdateData::UpdatePlayerPositionAndState(m_player->getPosition(), STATE::LIVE));
}

void CastScene::SyncBallPosition(float dt)
{
	if (m_died) return;
	if (m_balls.size() == 0) return;
	vector<Vec2> pos;
	vector<Vec2> vec;
	for (int i = 0; i < m_balls.size(); i++)
	{
		pos.push_back(m_balls[i]->getPosition());
		vec.push_back(m_balls[i]->getPhysicsBody()->getVelocity());
	}
	m_net->SendImmediate(UpdateData::UpdateAllBallPosition(pos.data(), vec.data(), m_balls.size()));
}

void CastScene::SyncBallPositionFromServer(float dt)
{
	if (m_died) return;
	if (!m_net->BposUpdated()) return;
	string jsonStr = m_net->GetBposData();
	Document d;
	d.Parse<rapidjson::kParseDefaultFlags>(jsonStr.c_str());
	if (d.HasParseError()) return;
	if (d.IsObject())
	{
		COMMAND com = (COMMAND)d["COMMAND"].GetInt();

		if (com == BPOS)
		{
			if (m_balls.size() == 0)
			{
				for (int i = 0; i < d["COUNT"].GetInt(); i++)
				{
					var sprite = BallSprite::create("redBall.png");
					float x = d["BALLS"][i]["X"].GetFloat();
					float y = d["BALLS"][i]["Y"].GetFloat();
					sprite->setPosition(x, y);
					sprite->setContentSize(Size(m_visibleSize.width / 20, m_visibleSize.width / 20));
					sprite->setName("ball");

					var circleCollider = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
					circleCollider->getShape(0)->setRestitution(1.0f);
					circleCollider->getShape(0)->setFriction(0.0f);
					circleCollider->getShape(0)->setDensity(1.0f);
					circleCollider->setGravityEnable(false);
					circleCollider->setCategoryBitmask(0x00000001);
					circleCollider->setCollisionBitmask(0x00000010);
					circleCollider->setContactTestBitmask(0xffffffff);
					Vect force = Vect(d["BALLS"][i]["VX"].GetFloat(), d["BALLS"][i]["VY"].GetFloat());
					circleCollider->applyForce(force);
					sprite->setPhysicsBody(circleCollider);

					this->addChild(sprite, 2);
					m_balls.push_back(sprite);
				}
			}
			else
			{
				for (int i = 0; i < m_balls.size(); i++)
				{
					m_balls[i]->setPosition(d["BALLS"][i]["X"].GetFloat(), d["BALLS"][i]["Y"].GetFloat());
					m_balls[i]->getPhysicsBody()->setVelocity(Vec2(d["BALLS"][i]["VX"].GetFloat(), d["BALLS"][i]["VY"].GetFloat()));
				}
			}
		}
	}
}

