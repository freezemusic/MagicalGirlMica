/*
 * entity_db.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <deque>
#include <set>

#include "listener_manager.h"
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
	typedef std::function<void(const Entity*)> EntityListener;

	EntityDb();
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

	/**
	 * Add a listener to be called after an entity is being added
	 *
	 * @param l
	 * @return
	 */
	Uint addAddEntityListener(const EntityListener &l)
	{
		return m_add_listeners.addListener(l);
	}

	void removeAddEntityListener(const Uint id)
	{
		m_add_listeners.removeListener(id);
	}

	/**
	 * Add a listener to be called before an entity is being removed
	 *
	 * @param l
	 * @return
	 */
	Uint addRemoveEntityListener(const EntityListener &l)
	{
		return m_remove_listeners.addListener(l);
	}

	void removeRemoveEntityListener(const Uint id)
	{
		m_remove_listeners.removeListener(id);
	}

private:
	std::deque<Entity> m_entities;
	std::set<Uint> m_unused_ids;
	ListenerManager<EntityListener> m_add_listeners;
	ListenerManager<EntityListener> m_remove_listeners;
};


}
