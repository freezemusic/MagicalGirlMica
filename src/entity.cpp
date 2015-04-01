/*
 * entity.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <cassert>

#include <algorithm>
#include <deque>
#include <memory>

#include "com/component.h"
#include "entity.h"

using namespace mica::com;
using namespace std;

namespace mica
{

Entity::Entity(Config &&conf)
		: m_id(conf.id),
		  m_coms(std::move(conf.coms))
{
	sortComponents();
	buildKey();
}

Component* Entity::getComponent(const Uint com_id) const
{
	if (!hasComponent(com_id))
	{
		return nullptr;
	}

	auto it = std::lower_bound(m_coms.begin(), m_coms.end(), com_id,
			[](const unique_ptr<Component> &com, const Uint com_id)
			{
				return (com->getComponentId() < com_id);
			});
	assert(it != m_coms.end() && (*it)->getComponentId() == com_id);
	return it->get();
}

bool Entity::hasComponent(const Uint com_id) const
{
	return (com_id < m_com_key.size() && m_com_key[com_id]);
}

void Entity::sortComponents()
{
	std::sort(m_coms.begin(), m_coms.end(),
			[](const unique_ptr<Component> &a, const unique_ptr<Component> &b)
					-> bool
			{
				return (a->getComponentId() < b->getComponentId());
			});
}

void Entity::buildKey()
{
	m_com_key.resize(m_coms.back()->getComponentId());
	for (const auto &c : m_coms)
	{
		m_com_key[c->getComponentId()] = true;
	}
}

}
