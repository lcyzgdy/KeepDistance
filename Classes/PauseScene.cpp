#include "PauseScene.h"
using namespace cocos2d;

void PauseScene::ResumeGame(Ref* ref)
{
	Director::getInstance()->popScene();
}

Scene * PauseScene::createScene()
{
	return PauseScene::create();
}

bool PauseScene::init()
{
	var resumeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(PauseScene::ResumeGame, this));
	var menu = Menu::create(resumeItem, nullptr);

	var background = Sprite::createWithSpriteFrameName("background.png");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);
	background->setContentSize(Director::getInstance()->getVisibleSize());

	this->addChild(background);
	this->addChild(menu);
	return true;
}
