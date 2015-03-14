/*
 * controller.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <array>
#include <memory>

#include "button.h"
#include "controller.h"
#include "joystick.h"

using namespace std;

namespace mica
{

Controller::Controller(Config &&config)
		: m_joystick(std::move(config.joystick)),
		  m_buttons({std::move(config.buttons[0]), std::move(config.buttons[1])})
{}

}
