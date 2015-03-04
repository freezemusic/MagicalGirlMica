#include "World.h"

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

	bg = Background::create("bg.png");
	this->addChild(bg);


	std::string playerName = "Mica";
	ArmatureDataManager::getInstance()->addArmatureFileInfo(playerName + "0.png", playerName + "0.plist", playerName + ".ExportJson");
	player = Player::create(playerName);
	player->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height / 2);
	this->addChild(player, 1);
	//this->runAction(Follow::create(hero, Rect(0, 0, bgSize.width, visibleSize.height)));

	return true;
}