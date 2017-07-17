#include "BallPlayerLayer.h"


Layer * BallPlayerLayer::createLayer()
{
	return dynamic_cast<Layer*>(BallPlayerLayer::create());
}

bool BallPlayerLayer::init()
{
	var visibleSize = Director::getInstance()->getVisibleSize();
	//设置主角
	var player = BallSprite::createSprite("HelloWorld.png");
	player->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(player, 0);

	randomize();

	//给主角添加事件
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
		var newPos = t->getLocation() - m_playerOffset;

		float minX = player->getContentSize().width / 2;
		float maxX = visibleSize.width - minX;
		float minY = player->getContentSize().height / 2;
		float maxY = visibleSize.height - minY;

		// 越界检测
		float x = MIN(MAX(newPos.x, minX), maxX);
		float y = MIN(MAX(newPos.y, minY), maxY);
		player->setPosition(x, y);

	};
	listener->onTouchEnded = [](Touch* t, Event* e) {};
	//将事件与主角绑定
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, player);

	var physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = [=](PhysicsContact& p)
	{
		//out << dynamic_cast<SpriteWithPhysicsAndAnimation*>(p.getCurrentTarget())->getName() << endl;
		dynamic_cast<BallSprite*>(p.getCurrentTarget())->Hit();
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, player);

	this->scheduleUpdate();
	return true;
}

void BallPlayerLayer::update(float dt)
{

}
