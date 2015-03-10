#include <2d/CCCamera.h>
#include <2d/CCLayer.h>
#include <2d/CCScene.h>
#include <cocostudio/CCArmatureDataManager.h>

#include "res_manager.h"
#include "World.h"

namespace mica
{

Scene* World::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = World::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool World::init()
{
	if (!Layer::init())
	{
		return false;
	}

	bg = Background::create(ResManager::get().getBg("bg").c_str());
	this->addChild(bg);

	ArmatureDataManager::getInstance()->addArmatureFileInfo(
			ResManager::get().getCharacterArmature("Mica"));
	player = Player::create("Mica");
	player->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height / 2);
	this->addChild(player, 1);
	//this->runAction(Follow::create(hero, Rect(0, 0, bgSize.width, visibleSize.height)));

	return true;
}

}
