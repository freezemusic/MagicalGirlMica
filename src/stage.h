/*
 * stage.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <list>
#include <memory>

#include "stage_scene.h"

namespace mica
{

class Context;
class StageObject;

namespace input
{

class Controller;

}
}

namespace mica
{

/**
 * A stage
 */
class Stage
{
public:
	struct Config
	{
		input::Controller *controller;
	};

	Stage(const Context &context, const Config &config);
	virtual ~Stage();

	operator bool() const
	{
		return m_is_good;
	}

	StageScene* getScene()
	{
		return m_scene;
	}

	void addStageObject(std::unique_ptr<StageObject> &&obj);

	const std::list<std::unique_ptr<StageObject>>& getAllObjects()
	{
		return m_objs;
	}

protected:
	/**
	 * Invoked when the scene is being updated in a frame
	 *
	 * @param delta
	 */
	virtual void onSceneUpdate(const float delta);

	void setScene(StageScene *scene);

	void setGood(const bool flag)
	{
		m_is_good = flag;
	}

	const Context& getContext() const
	{
		return m_context;
	}

	input::Controller* getController() const
	{
		return m_controller;
	}

private:
	const Context &m_context;
	input::Controller *m_controller;

	std::list<std::unique_ptr<StageObject>> m_objs;
	StageScene *m_scene;
	bool m_is_good = false;
};

}
