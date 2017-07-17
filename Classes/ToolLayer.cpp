#include "ToolLayer.h"
using namespace cocos2d;

Layer * ToolLayer::createLayer()
{
	return dynamic_cast<Layer*>(ToolLayer::create());
}

bool ToolLayer::init()
{
	Layer::init();

	randomize();
	m_tool1DeltaT = random(100, 600);
	m_tool2DeltaT = random(100, 600);

	scheduleUpdate();
	return true;
}

void ToolLayer::update(float dt)
{
	m_tool1DeltaT--;
	m_tool2DeltaT--;
	if (m_tool1DeltaT == 0)
	{
		var tool = ToolSprite::createSprite("ufo1.png");
		tool->setPositionY(Director::getInstance()->getVisibleSize().height);
		tool->setPositionX(random(static_cast<int>(tool->getContentSize().width / 2), static_cast<int>(Director::getInstance()->getVisibleSize().width - tool->getContentSize().width / 2)));
		tool->setName("tool1");
		this->addChild(tool, 0);
		m_physicsObjects.push(dynamic_cast<SpriteWithPhysicsAndAnimation*>(tool));
		m_tool1DeltaT = random(100, 600);
	}

	if (m_tool2DeltaT == 0)
	{
		var tool = ToolSprite::createSprite("ufo2.png");
		tool->setPositionY(Director::getInstance()->getVisibleSize().height);
		tool->setPositionX(random(static_cast<int>(tool->getContentSize().width / 2), static_cast<int>(Director::getInstance()->getVisibleSize().width - tool->getContentSize().width / 2)));
		tool->setName("tool2");
		this->addChild(tool, 0);
		m_physicsObjects.push(dynamic_cast<SpriteWithPhysicsAndAnimation*>(tool));
		m_tool2DeltaT = random(100, 600);
	}
}
