#include "LoadingScene.h"
#include "AirPlaneScene.h"
using namespace cocos2d;

Scene * LoadingScene::createScene()
{
	return LoadingScene::create();
}

bool LoadingScene::init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
	var visibleSize = Director::getInstance()->getVisibleSize();
	var loadingAnim = AnimationCache::getInstance()->getAnimation("Loading");
	if (loadingAnim == nullptr)
	{
		var anim = Animation::create();
		for (int i = 1; i <= 4; i++)
		{
			var png = StringUtils::format("game_loading%d.png", i);
			anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
		}
		anim->setDelayPerUnit(0.07f);
		anim->setLoops(-1);
		AnimationCache::getInstance()->addAnimation(anim, "Loading");
		loadingAnim = AnimationCache::getInstance()->getAnimation("Loading");
	}

	var back = Sprite::create();
	back->setPosition(visibleSize.width / 2, visibleSize.height / 6);
	back->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
	Animate* animate = Animate::create(loadingAnim);
	back->runAction(animate);

	var touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [=](Touch* t, Event* e)
	{
		return true;
	};
	touchListener->onTouchMoved = [=](Touch* t, Event* e)
	{

	};
	touchListener->onTouchEnded = [=](Touch* t, Event* e)
	{
		var scene = AirPlaneScene::createScene();
		Director::getInstance()->pushScene(scene);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, back);

	var copyright = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	copyright->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	copyright->setContentSize(CCSizeMake(visibleSize.width/3*2, visibleSize.height/3*2));

	this->addChild(back);
	this->addChild(copyright);
	return true;
}
