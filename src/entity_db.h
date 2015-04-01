/*
 * entity_db.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <deque>
#include <set>

#include "misc_type.h"

namespace mica
{

class Entity;

}

namespace mica
{

class EntityDb
{
public:
	virtual ~EntityDb();

	/**
	 * Insert a new entity. The id of the entity must be unique across the db,
	 * otherwise this method will fail
	 *
	 * @param e
	 * @return true if successful, false otherwise
	 */
	bool addEntity(Entity &&e);
	void removeEntity(const Uint entityId);

	/**
	 * Return a new unique entity id ready to be used
	 *
	 * @return
	 */
	Uint newEntityId() const;

private:
	std::deque<Entity> m_entities;
	std::set<Uint> m_unused_ids;
};


}
