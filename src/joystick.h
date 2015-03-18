/*
 * joystick.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <libutils/type/coord.h>

#include "listenable.h"

namespace mica
{

/**
 * A joystick interface. Add listeners to be notified when the joystick moves
 */
class Joystick : public Listenable<Joystick>
{
public:
	virtual ~Joystick()
	{}

	operator bool() const
	{
		return m_is_good;
	}

	/**
	 * Return the joystick posittion, normalized to [-1000, 1000] in both axis
	 *
	 * @return
	 */
	virtual utils::type::Coord getPosition() const = 0;

protected:
	void setGood(const bool flag)
	{
		m_is_good = flag;
	}

private:
	bool m_is_good = false;
};

}
