/*
 * system.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "entity_db.h"

namespace mica
{
namespace sys
{

class System
{
public:
	explicit System(EntityDb *entity_db);
	virtual ~System();

protected:
	/**
	 * Call when a new entity is being added to the EntityDb
	 *
	 * @param e
	 * @see EntityDb::addAddEntityListener
	 */
	virtual void onNewEntity(const Entity *e) = 0;
	/**
	 * Call when an entity is being removed from the EntityDb
	 *
	 * @param e
	 * @see EntityDb::addRemoveEntityListener
	 */
	virtual void onRemoveEntity(const Entity *e) = 0;

private:
	EntityDb *m_entity_db;
	Uint m_add_listener_id;
	Uint m_remove_listener_id;
};

}
}
