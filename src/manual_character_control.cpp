/*
 * manual_character_control.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <libutils/type/coord.h>

#include "character.h"
#include "controller.h"
#include "manual_character_control.h"

using namespace utils::type;

namespace mica
{

ManualCharacterControl::ManualCharacterControl(const Config &config)
		: m_controller(config.controller)
{}

void ManualCharacterControl::control(Character *character)
{
	const Coord &pos = m_controller->getJoystickPosition(true);
	character->move(pos.x, pos.y);
}

}
