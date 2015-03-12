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

#include "misc_type.h"

namespace mica
{

template<typename T>
class Listenable
{
public:
	typedef std::function<void(T*)> Listener;

	Listenable();

	Uint addListener(const Listener &listener);
	void removeListener(const Uint id);

protected:
	~Listenable()
	{}

	void invokeListeners();

private:
	std::list<std::pair<Uint, Listener>> m_listeners;
	Uint m_id;
};

}

#include "listenable.tcc"
