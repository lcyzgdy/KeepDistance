#include "OtherBallLayer.h"

Layer * OtherBallLayer::createLayer()
{
	return dynamic_cast<Layer*>(OtherBallLayer::create());
}

bool OtherBallLayer::init()
{
	var visibleSize = Director::getInstance()->getVisibleSize();
	//ÉèÖÃµÐÈË
	randomize();

	m_visibleSize = Director::getInstance()->getVisibleSize();
	

	this->scheduleUpdate();
	return true;
}

void OtherBallLayer::update(float dt)
{

}
