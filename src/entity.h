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
	Entity();

	operator bool()
	{
		return (m_is_good && !m_components.empty());
	}

	void addComponent(std::unique_ptr<com::Component> &&com);
	void removeComponent(const Uint com_id);
	com::Component* getComponent(const Uint com_id);

	void setGood(const bool flag)
	{
		m_is_good = flag;
	}

private:
	std::unordered_map<Uint, std::unique_ptr<com::Component>> m_components;
	bool m_is_good = true;
};

}
