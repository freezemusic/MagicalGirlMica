/*
 * res.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "misc_type.h"

namespace mica
{

/**
 * Hold global constants
 */
class Res
{
public:
	static constexpr const char *kAppName = "Magical Girl Mica";
	static constexpr Uint kDesignW = 1024;
	static constexpr Uint kDesignH = 576;

	static constexpr Uint kOnScreenControlZ = 10;
	static constexpr Uint kNotificationZ = 20;

	static constexpr Uint kControlEventPriority = 1;
};

}
