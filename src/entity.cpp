/*
 * entity.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <algorithm>
#include <deque>
#include <memory>

#include <libutils/str/str_utils.h>

#include "com/component.h"
#include "entity.h"
#include "log.h"

using namespace mica::com;
using namespace std;
using namespace utils::str;

#define NS_TAG "mica::"
#define TAG NS_TAG "Entity::"

namespace mica
{

Entity::Entity(Config &&conf)
		: m_id(conf.id),
		  m_coms(std::move(conf.coms))
{
	sortComponents();
}

Component* Entity::getComponent(const Uint com_id)
{
	auto it = std::lower_bound(m_coms.begin(), m_coms.end(), com_id,
			[](const unique_ptr<Component> &com, const Uint com_id)
			{
				return (com->getComponentId() < com_id);
			});
	if (it != m_coms.end() && (*it)->getComponentId() == com_id)
	{
		return it->get();
	}
	else
	{
		LOG_D(TAG "getComponent", StrUtils::Concat("Invalid id: ", com_id));
		return nullptr;
	}
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

}
