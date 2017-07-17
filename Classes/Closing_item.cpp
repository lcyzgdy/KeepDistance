#include"Closing_item.h"
#include"cocos2d.h"
#include"Welcome_Scene.h"
#include"Switch_Scene.h"
#define VisibleSize Director::getInstance()->getVisibleSize()
using namespace cocos2d;

Closing_item::Closing_item() : Layer()
{}

Closing_item* Closing_item::create(float t)
{
	auto closing_item = new Closing_item();
	if (closing_item && closing_item->init(t))
	{
		closing_item->autorelease();
		return closing_item;
	}
	else
	{
		delete closing_item;
		closing_item = nullptr;
		return nullptr;
	}
}

bool Closing_item::init(float t)
{
	Layer::init();
	this->setContentSize(Director::getInstance()->getVisibleSize());
	/*auto restart = Sprite::create("Restart.png");
	auto menuItemRestart = MenuItemSprite::create(restart, restart, [=](Ref *) {
		Director::getInstance()->popScene();
	});
	*/
	auto back_to_begin = Sprite::create("Back.png");
	back_to_begin->setContentSize(Size(VisibleSize.width / 6, VisibleSize.height / 6));
	auto menuItemBackToBegin = MenuItemSprite::create(back_to_begin, back_to_begin, [=](Ref *) {
		auto scene = Welcome_Scene::create();
		Director::getInstance()->popScene();
	});

	auto exit = Sprite::create("Exit.png");
	exit->setContentSize(Size(VisibleSize.width / 6, VisibleSize.height / 6));
	auto menuItemExit = MenuItemSprite::create(exit, exit, [=](Ref *) {
		Director::getInstance()->end();
	});

	//设置存活时间图标
	auto time_show = Label::createWithSystemFont("Survival Time:", "Arial", 50);
	time_show->setPosition(700, 500);
	time_show->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	time_show->setColor(Color3B::BLACK);
	this->addChild(time_show);
	//设置存活时间数值
	auto time_survival = Label::createWithSystemFont(StringUtils::format("%.2fs", t), "Arial", 50);
	time_survival->setPosition(700 + time_show->getContentSize().width, 500);
	time_survival->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	time_survival->setColor(Color3B::BLACK);
	this->addChild(time_survival);


	//menuItemRestart->setPosition(1700, 900);
	menuItemBackToBegin->setPosition(1700, 750);
	menuItemExit->setPosition(1700, 600);


	auto menu = Menu::create();
	menu->setPosition(0, 0);
	//menu->addChild(menuItemRestart);
	menu->addChild(menuItemBackToBegin);
	menu->addChild(menuItemExit);
	this->addChild(menu);
	return true;
}