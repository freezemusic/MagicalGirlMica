/*
 * stage_scene.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <2d/CCScene.h>
#include <base/CCEventDispatcher.h>

#include "event_stage_scene.h"
#include "stage_scene.h"

using namespace cocos2d;

namespace mica
{

StageScene* StageScene::create()
{
	auto ret = new StageScene;
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

void StageScene::onEnterTransitionDidFinish()
{
	EventStageScene ev(this, true);
	getEventDispatcher()->dispatchEvent(&ev);

	Scene::onEnterTransitionDidFinish();
}

void StageScene::onExitTransitionDidStart()
{
	EventStageScene ev(this, false);
	getEventDispatcher()->dispatchEvent(&ev);

	Scene::onExitTransitionDidStart();
}

}
