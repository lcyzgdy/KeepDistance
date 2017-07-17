#include"HighScore_Item.h"
#include"cocos2d.h"
#include"Welcome_Scene.h"
#define VisibleSize Director::getInstance()->getVisibleSize()
using namespace cocos2d;

HighScore_item::HighScore_item()
{}

HighScore_item* HighScore_item::create()
{
	auto highscore_item = new HighScore_item();
	if(highscore_item && highscore_item->init())
	{
		highscore_item->autorelease();
		return highscore_item;
	}
	else
	{
		delete highscore_item;
		highscore_item = nullptr;
		return nullptr;
	}

}
bool HighScore_item::init()
{
	auto score = Sprite::create("Score.png");
	score->setPosition(VisibleSize.width/8,800);
	this->addChild(score);

	auto back = Sprite::create("Back.png");
	auto BackItem = MenuItemSprite::create(back,back,[=](Ref *){
		auto scene = Welcome_Scene::create();
		Director::getInstance()->replaceScene(scene);
	});

	BackItem->setPosition(VisibleSize.width/8,200);
	auto menu = Menu::create();
	menu->setPosition(0,0);
	menu->addChild(BackItem);
	this->addChild(menu);
	return true;
}