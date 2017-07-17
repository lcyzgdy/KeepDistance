#include"Switch_Scene.h"
#include"Background.h"
#include"Switch_item.h"
using namespace cocos2d;

Scene* Switch_Scene::create()
{
	auto switch_scene =Scene::create();
	auto background_layer = Background::create();
	auto switch_item_layer = Switch_item::create();
	switch_scene->addChild(background_layer);
	switch_scene->addChild(switch_item_layer);
	return switch_scene;
	
}