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

	Uint getPropertyId() const override
	{
		static Uint id = registerProperty();
		return id;
	}

	float getGravityRatio() const
	{
		return m_gravity_ratio;
	}

private:
	/**
	 * A ratio to the downward acceleration in normal situation, basically you
	 * want something <1
	 */
	float m_gravity_ratio;
};

}
}
