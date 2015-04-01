/*
 * velocity.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <array>

#include <libutils/math/vec.h>

#include "com/component.h"

namespace mica
{
namespace com
{

class Velocity : public Component
{
public:
	static Uint componentId()
	{
		static Uint id = registerComponent();
		return id;
	}

	Uint getComponentId() const override
	{
		return componentId();
	}

	utils::math::VecF2 velocity;
};

}
}
