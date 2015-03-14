/*
 * test_stage_scene.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "stage_scene.h"

namespace mica
{

class TestStageScene : public StageScene
{
public:
	static TestStageScene* create();

	bool init() override;
};

}
