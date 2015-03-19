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
	explicit TestStage(const Context &context);

private:
	bool initScene();
	bool initObjects();
};

}
