/*
 * glide_property.h
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

class GlideProperty : public Property
{
public:
	struct Config
	{
		float gravity_ratio;
	};

	explicit GlideProperty(const Config &config)
			: m_gravity_ratio(config.gravity_ratio)
	{}

	static Uint getPropertyId()
	{
		static Uint id = registerProperty();
		return id;
	}

	float getGravityRatio() const
	{
		return m_gravity_ratio;
	}

private:
	Uint getPropertyId_() const override
	{
		return getPropertyId();
	}

	/**
	 * A ratio to the downward acceleration in normal situation, basically you
	 * want something <1
	 */
	float m_gravity_ratio;
};

}
}
