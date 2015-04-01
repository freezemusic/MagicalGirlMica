/*
 * listener_manager.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <functional>
#include <list>
#include <utility>

#include "misc_type.h"

namespace mica
{

template<typename Listener_>
class ListenerManager final
{
public:
	typedef Listener_ Listener;

	ListenerManager();

	Uint addListener(const Listener &listener);
	void removeListener(const Uint id);

	template<typename... Param>
	void invokeListeners(Param... args);

private:
	std::list<std::pair<Uint, Listener>> m_listeners;
	Uint m_id;
};

}

#include "listener_manager.tcc"
