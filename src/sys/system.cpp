/*
 * system.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <functional>

#include "entity_db.h"
#include "system.h"

using namespace std;

namespace mica
{
namespace sys
{

System::System(EntityDb *entity_db)
		: m_entity_db(entity_db)
{
	m_add_listener_id = m_entity_db->addAddEntityListener(std::bind(
			&System::onNewEntity, this, placeholders::_1));
	m_remove_listener_id = m_entity_db->addRemoveEntityListener(std::bind(
			&System::onRemoveEntity, this, placeholders::_1));
}

System::~System()
{
	m_entity_db->removeAddEntityListener(m_add_listener_id);
	m_entity_db->removeRemoveEntityListener(m_remove_listener_id);
}

}
}
