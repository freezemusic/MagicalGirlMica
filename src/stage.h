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

class StageObject;

}

namespace mica
{

/**
 * A stage
 */
class Stage
{
public:
	Stage();
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

protected:
	void setScene(StageScene *scene);

	void setGood(const bool flag)
	{
		m_is_good = flag;
	}

private:
	std::list<std::unique_ptr<StageObject>> m_objs;
	StageScene *m_scene;
	bool m_is_good = false;
};

}
