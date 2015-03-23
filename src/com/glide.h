/*
 * glide.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "com/component.h"
#include "misc_type.h"

namespace mica
{
namespace com
{

class Glide : public Component
{
public:
	static Uint getComponentId()
	{
		static Uint id = registerComponent();
		return id;
	}

	/**
	 * A ratio to the downward acceleration in normal situation, basically you
	 * want something <1
	 */
	float gravity_ratio;

private:
	Uint getComponentId_() const override
	{
		return getComponentId();
	}
};

}
}
