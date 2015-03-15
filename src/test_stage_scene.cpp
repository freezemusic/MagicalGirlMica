/*
 * test_stage_scene.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <2d/CCSprite.h>
#include <cocostudio/CCArmatureDataManager.h>

#include "log.h"
#include "player.h"
#include "res_manager.h"
#include "stage_scene.h"
#include "test_stage_scene.h"

using namespace cocos2d;
using namespace cocostudio;

#define NS_TAG "mica::"
#define TAG NS_TAG "TestStageScene::"

namespace mica
{

TestStageScene* TestStageScene::create()
{
	auto ret = new TestStageScene;
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool TestStageScene::init()
{
	if (!StageScene::init())
	{
		return false;
	}

	auto *bg = Sprite::create(ResManager::get().getBg("bg").c_str());
	if (!bg)
	{
		LOG_W(TAG "init", "Failed while creating background sprite");
		return false;
	}
	bg->setAnchorPoint({0, 0});
	addChild(bg, 0);

	ArmatureDataManager::getInstance()->addArmatureFileInfo(
			ResManager::get().getCharacterArmature("Mica"));
	auto *player = Player::create("Mica");
	if (!player)
	{
		LOG_W(TAG "init", "Failed while creating player");
		return false;
	}
	player->setPosition(ResManager::getDesignW() / 2,
			ResManager::getDesignH() / 2);
	addChild(player, 1);

	return true;
}

}
