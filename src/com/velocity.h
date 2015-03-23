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
	static Uint getComponentId()
	{
		static Uint id = registerComponent();
		return id;
	}

	utils::math::VecF2 velocity;

private:
	Uint getComponentId_() const override
	{
		return getComponentId();
	}
};

}
}
