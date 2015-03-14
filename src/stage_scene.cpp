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
