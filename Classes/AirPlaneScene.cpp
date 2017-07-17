#include "AirPlaneScene.h"

using namespace cocos2d;

Scene * AirPlaneScene::createScene()
{
	return AirPlaneScene::create();
}

bool AirPlaneScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	m_visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	var phyx = PhysicsLayer::createLayer();
	phyx->setPosition(0, 0);
	phyx->setContentSize(CCSizeMake(m_visibleSize.width, m_visibleSize.height));
	phyx->setName("physics");
	m_physics = dynamic_cast<PhysicsLayer*>(phyx);

	var player = PlayerLayer::createLayer();
	player->setPosition(0, 0);
	player->setContentSize(CCSizeMake(m_visibleSize.width, m_visibleSize.height));
	player->setName("player");
	m_player = dynamic_cast<PlayerLayer*>(player);

	var background = BackgroundLayer::createLayer();
	background->setPosition(0, 0);
	background->setContentSize(CCSizeMake(m_visibleSize.width, m_visibleSize.height));
	background->setName("background");

	var enemy = EnemyLayer::createLayer();
	enemy->setPosition(0, 0);
	enemy->setContentSize(CCSizeMake(m_visibleSize.width, m_visibleSize.height));
	enemy->setName("enemy");
	m_enemy = dynamic_cast<EnemyLayer*>(enemy);

	var tool = ToolLayer::createLayer();
	tool->setPosition(0, 0);
	tool->setContentSize(CCSizeMake(m_visibleSize.width, m_visibleSize.height));
	tool->setName("tool");
	m_tool = dynamic_cast<ToolLayer*>(tool);

	var ui = UILayer::createLayer();
	ui->setPosition(0, 0);
	ui->setContentSize(CCSizeMake(m_visibleSize.width, m_visibleSize.height));
	ui->setName("ui");
	m_ui = dynamic_cast<UILayer*>(ui);

	if (m_enemy == nullptr || m_player == nullptr)
	{
		return false;
	}

	this->addChild(phyx, 0);
	this->addChild(background, 1);
	this->addChild(enemy, 2);
	this->addChild(player, 2);
	this->addChild(tool, 2);
	this->addChild(ui, 3);

	this->scheduleUpdate();
	return true;
}

void AirPlaneScene::update(float dt)
{
	while (!m_enemy->m_physicsObjects.empty())
	{
		m_physics->Add(m_enemy->m_physicsObjects.front());
		m_enemy->m_physicsObjects.pop();
	}
	while (!m_player->m_physicsObjects.empty())
	{
		m_physics->Add(m_player->m_physicsObjects.front());
		m_player->m_physicsObjects.pop();
	}
	while (!m_tool->m_physicsObjects.empty())
	{
		m_physics->Add(m_tool->m_physicsObjects.front());
		m_tool->m_physicsObjects.pop();
	}

	m_ui->SetDazhaoCount(dynamic_cast<PlaneSprite*>(getChildByName("player")->getChildByName("player"))->GetDazhaoCount());

	sort(m_enemy->m_scorePool.begin(), m_enemy->m_scorePool.end(), Cmp);
	while (m_enemy->m_scorePool.size() > 0 && m_enemy->m_scorePool[0]->Died())
	{
		var a = m_enemy->m_scorePool[0];
		m_ui->AddScore(a->GetScore());
		dynamic_cast<PlaneSprite*>(m_player->getChildByName("player"))->AddTotalScore(a->GetScore());
		m_enemy->m_scorePool[0]->Remove();
		m_enemy->m_scorePool.erase(m_enemy->m_scorePool.begin());
	}
}
