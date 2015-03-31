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

	Entity()
			: m_id(kInvalidId)
	{}

	explicit Entity(const Uint id)
			: m_id(id)
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
