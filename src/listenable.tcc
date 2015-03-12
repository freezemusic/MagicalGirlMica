/*
 * listenable.tcc
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <functional>
#include <list>
#include <utility>

#include "listenable.h"
#include "misc_type.h"

namespace mica
{

template<typename T>
Listenable<T>::Listenable()
		: m_id(0)
{}

template<typename T>
Uint Listenable<T>::addListener(const Listener &listener)
{
	m_listeners.push_back(make_pair(m_id, listener));
	return m_id++;
}

template<typename T>
void Listenable<T>::removeListener(const Uint id)
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
void Listenable<T>::invokeListeners()
{
	for (auto &l : m_listeners)
	{
		l.second(static_cast<T*>(this));
	}
}

}
