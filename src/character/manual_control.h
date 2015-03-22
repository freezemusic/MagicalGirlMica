/*
 * manual_control.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "character/control.h"

namespace mica
{

class Controller;

namespace character
{

class Character;

}
}

namespace mica
{
namespace character
{

/**
 * A Control that connects with the Controller
 */
class ManualControl : public Control
{
public:
	struct Config
	{
		Controller *controller;
	};

	explicit ManualControl(const Config &config);

	void control(Character *character) override;

private:
	Controller *m_controller;
};

}
}
