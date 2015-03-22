/*
 * manual_control.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <libutils/type/coord.h>

#include "character/character.h"
#include "character/control.h"
#include "character/manual_control.h"
#include "controller.h"

using namespace utils::type;

namespace mica
{
namespace character
{

ManualControl::ManualControl(const Config &config)
		: m_controller(config.controller)
{}

void ManualControl::control(Character *character)
{
	const Coord &pos = m_controller->getJoystickPosition(true);
	character->move(pos.x, pos.y);
}

}
}
