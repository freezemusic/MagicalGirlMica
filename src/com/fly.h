/*
 * fly.h
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

class Fly : public Component
{
public:
	static Uint getComponentId()
	{
		static Uint id = registerComponent();
		return id;
	}

private:
	Uint getComponentId_() const override
	{
		return getComponentId();
	}
};

}
}
