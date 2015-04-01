/*
 * entity.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "misc_type.h"

namespace mica
{

class Entity final
{
public:
	static constexpr Uint kInvalidId = (Uint)-1;

	struct Config
	{
		Uint id = kInvalidId;
	};

	Entity()
			: m_id(kInvalidId)
	{}

	explicit Entity(const Config &conf)
			: m_id(conf.id)
	{}

	operator bool()
	{
		return (m_id != kInvalidId);
	}

	Uint getId() const
	{
		return m_id;
	}

private:
	Uint m_id;
};

}
