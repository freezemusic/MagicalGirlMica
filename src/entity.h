/*
 * entity.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "com/component.h"
#include "misc_type.h"

namespace mica
{

class Entity final
{
public:
	explicit Entity(const Uint id)
			: m_id(id)
	{}

	operator bool()
	{
		return m_is_good;
	}

	void setGood(const bool flag)
	{
		m_is_good = flag;
	}

	Uint getId() const
	{
		return m_id;
	}

private:
	Uint m_id;
	bool m_is_good = true;
};

}
