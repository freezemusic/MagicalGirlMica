/*
 * jump_property.h
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

class JumpProperty : public Property
{
public:
	struct Config
	{
		Uint count;
	};

	explicit JumpProperty(const Config &config)
			: m_count(config.count)
	{}

	Uint getPropertyId() const override
	{
		static Uint id = registerProperty();
		return id;
	}

	Uint getCount() const
	{
		return m_count;
	}

private:
	/// Double jumping kung-fu fighter :)?
	Uint m_count;
};

}
}
