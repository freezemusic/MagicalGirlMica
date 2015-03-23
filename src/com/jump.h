/*
 * jump.h
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

class Jump : public Component
{
public:
	struct Config
	{
		Uint count;
	};

	explicit Jump(const Config &config)
			: m_count(config.count)
	{}

	static Uint getComponentId()
	{
		static Uint id = registerComponent();
		return id;
	}

	Uint getCount() const
	{
		return m_count;
	}

private:
	Uint getComponentId_() const override
	{
		return getComponentId();
	}

	/// Double jumping kung-fu fighter :)?
	Uint m_count;
};

}
}
