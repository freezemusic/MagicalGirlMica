/*
 * stage.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <list>
#include <memory>

#include <base/CCEventDispatcher.h>

#include "stage.h"
#include "stage_object.h"
#include "stage_scene.h"

using namespace std;

namespace mica
{

Stage::Stage()
		: m_scene(nullptr)
{}

Stage::~Stage()
{
	// Clear the scene first as it contains the view from stage objects
	setScene(nullptr);
	m_objs.clear();
}

void Stage::setScene(StageScene *scene)
{
	if (m_scene)
	{
		m_scene->getEventDispatcher()->removeEventListenersForTarget(m_scene);
		m_scene->removeFromParent();
		m_scene->release();
	}
	m_scene = scene;
	if (m_scene)
	{
		m_scene->retain();
		setGood(true);
	}
	else
	{
		setGood(false);
	}
}

void Stage::addStageObject(unique_ptr<StageObject> &&obj)
{
	if (m_scene)
	{
		m_scene->addChild(obj->getView());
	}
	m_objs.push_back(std::move(obj));
}

}
