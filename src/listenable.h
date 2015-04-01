/*
 * listenable.h
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

/**
 * Deprecated, use ListenerManager instead
 */
template<typename T>
class Listenable
{
public:
	typedef std::function<void(T*)> Listener;

	Uint addListener(const Listener &listener)
	{
		return m_manager.addListener(listener);
	}

	void removeListener(const Uint id)
	{
		m_manager.removeListener(id);
	}

protected:
	~Listenable()
	{}

	void invokeListeners()
	{
		m_manager.invokeListeners(static_cast<T*>(this));
	}

private:
	ListenerManager<Listener> m_manager;
};

}
