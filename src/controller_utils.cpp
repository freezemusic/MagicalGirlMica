/*
 * controller_utils.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <cstdlib>

#include <libutils/type/coord.h>

#include "controller_utils.h"

using namespace utils::type;

namespace mica
{

Coord ControllerUtils::filterDeadzone(const Coord &coord)
{
	return {(abs(coord.x) < kDeadzone) ? 0 : coord.x,
			(abs(coord.y) < kDeadzone) ? 0 : coord.y};
}

}
