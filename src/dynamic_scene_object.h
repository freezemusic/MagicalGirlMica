/*
 * dynamic_scene_object.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <cocostudio/CCArmature.h>

#include "scene_object.h"

namespace mica
{

class DynamicSceneObject : public SceneObject
{
public:
	DynamicSceneObject();
	virtual ~DynamicSceneObject();

	cocostudio::Armature* getView() override
	{
		return m_view;
	}

protected:
	void setView(cocostudio::Armature *view);

private:
	cocostudio::Armature *m_view;
};

}
