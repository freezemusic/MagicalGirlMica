/*
 * test_stage.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "stage.h"

namespace mica
{

class TestStage : public Stage
{
public:
	TestStage();

private:
	bool initScene();
};

}