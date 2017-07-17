#include"Begining_item.h"
#include"cocos2d.h"
#include"GameOverScene.h"
#include"Switch_Scene.h"
#include"HighScore_Scene.h"
#include "SimpleAudioEngine.h"
#include"CastScene.h"
#include"SingleCastScene.h"
using namespace CocosDenshion;
#define VisibleSize Director::getInstance()->getVisibleSize()
using namespace cocos2d;

Begining_item::Begining_item()
{}

Begining_item* Begining_item::create()
{
	auto begining_item = new Begining_item();
	if (begining_item && begining_item->init())
	{
		begining_item->autorelease();
		return begining_item;
	}
	else
	{
		delete begining_item;
		begining_item = nullptr;
		return nullptr;
	}
}

bool Begining_item::init()
{
	//Ô¤¼ÓÔØÒôĞ§
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("begining_music.mp3");
	//SimpleAudioEngine::getInstance()->preloadEffect("big_spaceship_flying.mp3");

	auto single_start = Sprite::create("Single start.png");
	single_start->setContentSize(Size(VisibleSize.width / 6, VisibleSize.height / 6));
	auto menuItemSingleStart = MenuItemSprite::create(single_start, single_start, [=](Ref *) {
		auto scene = SingleCastScene::createWithPhysics();
		var tran = TransitionFade::create(1.0f, scene);
		Director::getInstance()->pushScene(scene);
	});

	auto online_start = Sprite::create("Online start.png");
	online_start->setContentSize(Size(VisibleSize.width / 6, VisibleSize.height / 6));
	auto menuItemOnlineStart = MenuItemSprite::create(online_start, online_start, [=](Ref *) {
		var castScene = CastScene::createSceneWithPhysics();
		var tran = TransitionFade::create(1.0f, castScene);
		Director::getInstance()->pushScene(tran);
	});
	/*
	auto high_score = Sprite::create("High score.png");
	auto menuItemHighScore = MenuItemSprite::create(high_score, high_score, [=](Ref *) {
		auto scene = HighScore_Scene::create();
		Director::getInstance()->pushScene(scene);

	});
	*/
	auto exit = Sprite::create("Exit.png");
	exit->setContentSize(Size(VisibleSize.width / 6, VisibleSize.height / 6));
	auto menuItemExit = MenuItemSprite::create(exit, exit, [=](Ref *) {
		Director::getInstance()->end();
	});
	menuItemSingleStart->setPosition(VisibleSize.width / 2, 650);
	//menuItemSingleStart->setContentSize(Size(VisibleSize.width / 6, VisibleSize.height / 6));
	menuItemOnlineStart->setPosition(VisibleSize.width / 2, 500);
	//menuItemOnlineStart->setContentSize(Size(VisibleSize.width / 6, VisibleSize.height / 6));
	//menuItemHighScore->setPosition(VisibleSize.width / 2, 350);
	menuItemExit->setPosition(VisibleSize.width / 2, 350);
	//menuItemExit->setContentSize(Size(VisibleSize.width / 6, VisibleSize.height / 6));

	auto menu = Menu::create();
	menu->setPosition(0, 0);
	menu->addChild(menuItemSingleStart);
	menu->addChild(menuItemOnlineStart);
	//menu->addChild(menuItemHighScore);
	menu->addChild(menuItemExit);
	this->addChild(menu);

	return true;
}

