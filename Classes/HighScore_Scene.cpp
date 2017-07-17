#include"HighScore_Scene.h"
#include"HighScore_Item.h"
#include"Background_end.h"
#include"Welcome_Scene.h"
using namespace cocos2d;

Scene* HighScore_Scene::create()
{
	auto highscore_scene = Scene::create();
	auto background_end = Background_end::create();
	auto item_highscore = HighScore_item::create();
	highscore_scene->addChild(background_end);
	highscore_scene->addChild(item_highscore);
	return highscore_scene;

}