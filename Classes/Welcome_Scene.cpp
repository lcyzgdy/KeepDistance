#include"Welcome_Scene.h"
#include"Background.h"
#include"Begining_item.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

using namespace cocos2d;

Scene* Welcome_Scene::create()
{
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3f);
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("begining_music.mp3", true);

	SimpleAudioEngine::getInstance()->playBackgroundMusic("background.wav", true);
	auto welcome_scene = Scene::create();
	auto background_layer = Background::create();
	auto begining_item_layer = Begining_item::create();
	welcome_scene->addChild(background_layer);
	welcome_scene->addChild(begining_item_layer);


	return welcome_scene;

}