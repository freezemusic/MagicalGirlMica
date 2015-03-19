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

class Context;

}

namespace mica
{

class TestStage : public Stage
{
public:
	typedef Stage::Config Config;

	TestStage(const Context &context, const Config &config);

private:
	bool initScene();
	bool initObjects();
};

}
