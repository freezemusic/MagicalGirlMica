/*
 * listener_manager.tcc
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <functional>
#include <list>
#include <utility>

#include "listener_manager.h"
#include "misc_type.h"

namespace mica
{

template<typename T>
ListenerManager<T>::ListenerManager()
		: m_id(0)
{}

template<typename T>
Uint ListenerManager<T>::addListener(const Listener &listener)
{
	m_listeners.push_back(make_pair(m_id, listener));
	return m_id++;
}

template<typename T>
void ListenerManager<T>::removeListener(const Uint id)
{
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it)
	{
		if (it->first == id)
		{
			m_listeners.erase(it);
			return;
		}
	}
}

template<typename T>
template<typename... Param>
void ListenerManager<T>::invokeListeners(Param... args)
{
	for (auto &l : m_listeners)
	{
		l.second(args...);
	}
}

}
