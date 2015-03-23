/*
 * entity.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <memory>
#include <unordered_map>

#include "com/component.h"
#include "entity.h"
#include "misc_type.h"

using namespace mica::com;
using namespace std;

namespace mica
{

Entity::Entity()
{
	// We want to prevent a later rehash at all cost
	m_components.reserve(50);
}

void Entity::addComponent(unique_ptr<Component> &&com)
{
	const Uint id = Component::getComponentId(com.get());
	m_components[id] = std::move(com);
}

void Entity::removeComponent(const Uint com_id)
{
	m_components.erase(com_id);
}

Component* Entity::getComponent(const Uint com_id)
{
	auto it = m_components.find(com_id);
	return ((it == m_components.end()) ? nullptr : it->second.get());
}

}
