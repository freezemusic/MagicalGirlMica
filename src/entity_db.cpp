/*
 * entity_db.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <cstddef>

#include <deque>
#include <set>

#include <libutils/str/str_utils.h>

#include "entity.h"
#include "entity_db.h"
#include "log.h"

using namespace utils::str;

#define NS_TAG "mica::"
#define TAG NS_TAG "EntityDb::"

namespace mica
{

EntityDb::~EntityDb()
{}

bool EntityDb::addEntity(Entity &&e)
{
	if (e.getId() >= m_entities.size())
	{
		const size_t size_diff = e.getId() + 1 - m_entities.size();
		for (size_t i = 0; i < size_diff - 1; ++i)
		{
			m_unused_ids.insert(m_entities.size() + i);
		}
		m_entities.resize(e.getId() + 1);
		m_entities.back() = std::move(e);
		return true;
	}
	else if (m_unused_ids.find(e.getId()) != m_unused_ids.end())
	{
		m_unused_ids.erase(e.getId());
		m_entities[e.getId()] = std::move(e);
		return true;
	}
	else
	{
		LOG_E(TAG "addEntity", StrUtils::Concat("Invalid id: ", e.getId()));
		return false;
	}
}

void EntityDb::removeEntity(const Uint entityId)
{
	if (entityId >= m_entities.size())
	{
		LOG_E(TAG "removeEntity", StrUtils::Concat("Invalid id: ", entityId));
		return;
	}
	m_entities[entityId] = Entity();
	m_unused_ids.insert(entityId);
}

Uint EntityDb::newEntityId() const
{
	if (!m_unused_ids.empty())
	{
		return *m_unused_ids.begin();
	}
	else
	{
		return m_entities.size();
	}
}

}
