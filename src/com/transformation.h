/*
 * transformation.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <array>

#include <libutils/type/coord.h>

#include "com/component.h"

namespace mica
{
namespace com
{

class Transformation : public Component
{
public:
	static Uint getComponentId()
	{
		static Uint id = registerComponent();
		return id;
	}

	utils::type::Coord position;
	std::array<float, 3> orientation;

private:
	Uint getComponentId_() const override
	{
		return getComponentId();
	}
};

}
}
