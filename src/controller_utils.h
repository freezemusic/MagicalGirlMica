/*
 * controller_utils.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <libutils/type/coord.h>

namespace mica
{

/**
 * Utility funcations around the Controller
 */
class ControllerUtils
{
public:
	ControllerUtils() = delete;

	/**
	 * Filter the joystick position with deadzone
	 *
	 * @param coord
	 * @return
	 */
	static utils::type::Coord filterDeadzone(const utils::type::Coord &coord);

private:
	static constexpr int kDeadzone = 80;
};

}
