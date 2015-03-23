/*
 * fly_property.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "character/property.h"
#include "misc_type.h"

namespace mica
{
namespace character
{

class FlyProperty : public Property
{
public:
	static Uint getPropertyId()
	{
		static Uint id = registerProperty();
		return id;
	}

private:
	Uint getPropertyId_() const override
	{
		return getPropertyId();
	}
};

}
}
