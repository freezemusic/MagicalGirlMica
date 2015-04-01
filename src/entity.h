/*
 * entity.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <deque>
#include <memory>

#include "com/component.h"
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
		std::deque<std::unique_ptr<com::Component>> coms;
	};

	Entity()
			: m_id(kInvalidId)
	{}

	explicit Entity(Config &&conf);

	operator bool()
	{
		return (m_id != kInvalidId);
	}

	Uint getId() const
	{
		return m_id;
	}

	com::Component* getComponent(const Uint com_id);

private:
	/**
	 * Sort the components in ascending order based on the component id
	 */
	void sortComponents();

	Uint m_id;
	std::deque<std::unique_ptr<com::Component>> m_coms;
};

}
