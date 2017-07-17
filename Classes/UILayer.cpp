#include "UILayer.h"
#include"PauseScene.h"
using namespace cocos2d;

Layer * UILayer::createLayer()
{
	return dynamic_cast<Layer*>(UILayer::create());
}

bool UILayer::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();

	TTFConfig ttfConfig("font/consola.ttf", 24);
	var scoreTTF = Label::createWithTTF(ttfConfig, "ASDFGHJKL");
	scoreTTF->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
	scoreTTF->setAnchorPoint(Vec2::ZERO);
	scoreTTF->setPosition(3, 3);
	scoreTTF->setColor(Color3B::RED);
	m_labelScore = scoreTTF;

	var dazhaoTTF = Label::createWithTTF(ttfConfig, "ASDFGHJKL:");
	//scoreTTF->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
	dazhaoTTF->setAnchorPoint(Vec2(getContentSize().width, getContentSize().height));
	dazhaoTTF->setPosition(m_visibleSize.width - 50, 3);
	dazhaoTTF->setColor(Color3B::RED);
	m_labelDazhaoCount = dazhaoTTF;

	//var dazhaoItem = MenuItemImage::create(, "bomb.png", );
	var dazhaoItem = MenuItemImage::create();
	dazhaoItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb.png"));
	dazhaoItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb.png"));
	dazhaoItem->setCallback(CC_CALLBACK_1(UILayer::Dazhao, this));
	dazhaoItem->setPositionX(100);

	var pauseItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png", CC_CALLBACK_1(UILayer::PauseGame, this));
	pauseItem->setPosition(getPositionX() + 100, getPositionY() - 100);

	var menu = Menu::create(dazhaoItem, pauseItem, nullptr);

	//menu->setPosition(Vec2::ZERO);

	m_score = 0;
	m_dazhaoCount = 0;

	this->addChild(scoreTTF, 0);
	this->addChild(dazhaoTTF, 0);
	this->addChild(menu, 0);

	this->scheduleUpdate();
	return true;
}

void UILayer::update(float dt)
{
	m_labelScore->setString("Score: " + IntToString(m_score));
	m_labelDazhaoCount->setString("X" + IntToString(m_dazhaoCount));
}

void UILayer::AddScore(int score)
{
	m_score += score;
}

void UILayer::SetDazhaoCount(int h)
{
	m_dazhaoCount = h;
}

void UILayer::PauseGame(Ref* ref)
{
	var scene = PauseScene::createScene();
	var transitions = TransitionMoveInL::create(0.2f, scene);
	Director::getInstance()->pushScene(transitions);
}

void UILayer::Dazhao(Ref* ref)
{
	if (m_dazhaoCount <= 0) return;
	var plane = dynamic_cast<PlaneSprite*>(this->getParent()->getChildByName("player")->getChildByName("player"));
	plane->Dazhao();
	m_dazhaoCount--;
}
