#include <memory>

#include <2d/CCCamera.h>
#include <2d/CCLayer.h>
#include <2d/CCScene.h>
#include <cocostudio/CCArmatureDataManager.h>

#include "area_joystick.h"
#include "log.h"
#include "res_manager.h"
#include "World.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace std;

#define NS_TAG "mica::"
#define TAG NS_TAG "World::"

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

	Sprite *bg = Sprite::create(ResManager::get().getBg("bg").c_str());
	if (!bg)
	{
		LOG_W(TAG "init", "Failed while creating background sprite");
		return false;
	}
	bg->setAnchorPoint({0, 0});
	this->addChild(bg);

	ArmatureDataManager::getInstance()->addArmatureFileInfo(
			ResManager::get().getCharacterArmature("Mica"));
	player = Player::create("Mica");
	player->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height / 2);
	this->addChild(player, 1);
	//this->runAction(Follow::create(hero, Rect(0, 0, bgSize.width, visibleSize.height)));

	AreaJoystick::Config joystick_conf;
	//joystick_conf.is_visible = true;
	joystick_conf.rect.size.w = ResManager::getDesignW() / 2;
	joystick_conf.rect.size.h = ResManager::getDesignH();
	m_joystick = make_unique<AreaJoystick>(joystick_conf);
	if (!*m_joystick)
	{
		LOG_W(TAG "init", "Failed while creating AreaJoystick");
		return false;
	}
	addChild(m_joystick->getView(), 2);
	return true;
}

}
