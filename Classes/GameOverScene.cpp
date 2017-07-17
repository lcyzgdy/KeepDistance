#include"GameOverScene.h"
#include"Background_end.h"
#include"Closing_item.h"
using namespace cocos2d;

Scene* GameOverScene::create(float t)
{
	auto gameoverscene = Scene::create();
	gameoverscene->setContentSize(Director::getInstance()->getVisibleSize());
	auto background_end = Background_end::create();
	auto item_end = Closing_item::create(t);
	gameoverscene->addChild(background_end);
	gameoverscene->addChild(item_end);

	return gameoverscene;
}
