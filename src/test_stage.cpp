/*
 * test_stage.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <memory>

#include <2d/CCSprite.h>
#include <base/CCScheduler.h>

#include "character/character.h"
#include "character/manual_character_control.h"
#include "character/null_character_control.h"
#include "context.h"
#include "log.h"
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

TestStage::TestStage(const Context &context, const Config &config)
		: Stage(context, config)
{
	setGood(initScene() && initObjects());
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
			? Sprite::create(getContext().getResManager()->getBg("bg").c_str())
			: Sprite::create(getContext().getResManager()->getBg("bg2").c_str());
	if (!bg)
	{
		LOG_W(TAG "initScene", "Failed while creating background sprite");
		return false;
	}
	bg->setAnchorPoint({0, 0});
	scene->addChild(bg, 0);

	auto welcome = [this](float)
			{
				getContext().getNotificationManager()->addNotifiction(
						make_unique<Toast>(getContext(), "Test Stage"));
			};
	scene->getScheduler()->schedule(welcome, scene, 1.0f, 0, 0.0f, false, "toast");

	setScene(scene);
	return *this;
}

bool TestStage::initObjects()
{
	using namespace character;

	Character::Config char_conf;
	char_conf.identifier = "Mica";
	char_conf.pos = {100, 300};
	ManualCharacterControl::Config char_control_conf;
	char_control_conf.controller = getController();
	char_conf.control = make_unique<ManualCharacterControl>(char_control_conf);
	auto character = make_unique<Character>(getContext(), std::move(char_conf));
	if (!character || !*character)
	{
		LOG_W(TAG "initObjects", "Failed while creating Character");
		return false;
	}
	addStageObject(std::move(character));
	return true;
}

}
