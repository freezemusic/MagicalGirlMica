/*
 * entity.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>
#include <vector>

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
		std::vector<std::unique_ptr<com::Component>> coms;
	};

	Entity()
			: m_id(kInvalidId)
	{}

	explicit Entity(Config &&conf);

	explicit operator bool() const
	{
		return (m_id != kInvalidId);
	}

	Uint getId() const
	{
		return m_id;
	}

	com::Component* getComponent(const Uint com_id) const;
	/**
	 * Return if a specific component is included in this entity
	 *
	 * @param com_id
	 * @return
	 */
	bool hasComponent(const Uint com_id) const;

private:
	/**
	 * Sort the components in ascending order based on the component id
	 */
	void sortComponents();
	/**
	 * Build a key that represents the components included in this entity
	 *
	 * @note This method expect the components to be sorted already
	 */
	void buildKey();

	Uint m_id;
	std::vector<bool> m_com_key;
	std::vector<std::unique_ptr<com::Component>> m_coms;
};

}
