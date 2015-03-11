/*
 * joystick.h
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

class Joystick
{
public:
	typedef std::function<void(Joystick*)> OnMoveListener;

	Joystick();
	virtual ~Joystick();

	operator bool() const
	{
		return m_is_good;
	}

	Uint addOnMoveListener(const OnMoveListener &listener);
	void removeOnMoveListener(const Uint id);

	virtual int getX() const = 0;
	virtual int getY() const = 0;

protected:
	void invokeOnMoveListeners();

	void setGood(const bool flag)
	{
		m_is_good = flag;
	}

private:
	std::list<std::pair<Uint, OnMoveListener>> m_listeners;
	Uint m_id;

	bool m_is_good = true;
};

}
