/*
 * stage.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <functional>
#include <list>
#include <memory>

#include <base/CCEventDispatcher.h>
#include <base/CCScheduler.h>

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

void Stage::onSceneUpdate(const float)
{
	auto it = m_objs.begin();
	while (it != m_objs.end())
	{
		if (!**it)
		{
			it = m_objs.erase(it);
		}
		else
		{
			++it;
		}
	}
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
		m_scene->getScheduler()->schedule(std::bind(&Stage::onSceneUpdate, this,
				placeholders::_1), m_scene, 0.0f, false, "update");
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
