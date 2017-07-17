#include"Switch_item.h"
#include"cocos2d.h"
#include"Welcome_Scene.h"
//#include"Leve1_Scene.h"
#define VisibleSize Director::getInstance()->getVisibleSize()
using namespace cocos2d;

Switch_item::Switch_item()
{
}

Switch_item* Switch_item::create()
{
	auto switch_item = new Switch_item();
	if(switch_item && switch_item->init())
	{
		switch_item->autorelease();
		return switch_item;
	}
	else
	{
		delete switch_item;
		switch_item = nullptr;
		return nullptr;
	}
}

bool Switch_item::init()
{
	auto level_1 = Sprite::create("Level_1.png");
	auto menuItemLevel_1 = MenuItemSprite::create(level_1,level_1,[=](Ref *){
		//auto scene = Level_1::create();
		//Director::getInstance()->replaceScene(scne);
	});

	auto level_2 = Sprite::create("Level_2.png");
	auto menuItemLevel_2 = MenuItemSprite::create(level_2,level_2,[=](Ref *){
		//auto scene = Level_2::create();
		//Director::getInstance()->replaceScene(scne);
	});

	auto level_3 = Sprite::create("Level_3.png");
	auto menuItemLevel_3 = MenuItemSprite::create(level_3,level_3,[=](Ref *){
		//auto scene = Level_3::create();
		//Director::getInstance()->replaceScene(scne);
	});

	auto back_to_begin = Sprite::create("Back.png");
	auto menuItemBackToBegin = MenuItemSprite::create(back_to_begin,back_to_begin,[=](Ref *){
		auto scene = Welcome_Scene::create();
		Director::getInstance()->replaceScene(scene);
	});

	menuItemLevel_1->setPosition(VisibleSize.width/2,650);
	menuItemLevel_2->setPosition(VisibleSize.width/2,500);
	menuItemLevel_3->setPosition(VisibleSize.width/2,350);
	menuItemBackToBegin->setPosition(VisibleSize.width/2,200);

	auto menu = Menu::create();
	menu->setPosition(0,0);
	menu->addChild(menuItemLevel_1);
	menu->addChild(menuItemLevel_2);
	menu->addChild(menuItemLevel_3);
	menu->addChild(menuItemBackToBegin);
	this->addChild(menu);

	return true;
}
