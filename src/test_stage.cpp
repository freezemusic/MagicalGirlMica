/*
 * test_stage.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <memory>

#include <2d/CCSprite.h>
#include <base/CCScheduler.h>

#include "log.h"
#include "mgirl_mica.h"
#include "notification_manager.h"
#include "res_manager.h"
#include "stage_scene.h"
#include "test_stage.h"
#include "toast.h"

using namespace cocos2d;
using namespace std;

#define NS_TAG "mica::"
#define TAG NS_TAG "TestStage::"

namespace mica
{

TestStage::TestStage()
{
	setGood(initScene());
}

bool TestStage::initScene()
{
	static bool flag = false;

	auto *scene = StageScene::create();
	if (!scene)
	{
		LOG_E(TAG "initScene", "Failed while StageScene::create");
		return false;
	}

	auto *bg = !flag
			? Sprite::create(ResManager::get().getBg("bg").c_str())
			: Sprite::create(ResManager::get().getBg("bg2").c_str());
	if (!bg)
	{
		LOG_W(TAG "initScene", "Failed while creating background sprite");
		return false;
	}
	bg->setAnchorPoint({0, 0});
	scene->addChild(bg, 0);

//	ArmatureDataManager::getInstance()->addArmatureFileInfo(
//			ResManager::get().getCharacterArmature("Mica"));
//	auto *player = Player::create("Mica");
//	if (!player)
//	{
//		LOG_W(TAG "init", "Failed while creating player");
//		return false;
//	}
//	player->setPosition(ResManager::getDesignW() / 2,
//			ResManager::getDesignH() / 2);
//	addChild(player, 1);

	auto welcome = [this](float)
			{
				MgirlMica::get().getNotificationManager().addNotifiction(
						make_unique<Toast>("Test Stage"));
			};
	scene->getScheduler()->schedule(welcome, scene, 1.0f, 0, 0.0f, false, "toast");

	setScene(scene);
	return *this;
}

}
