/*
 * controller.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <cassert>

#include <memory>

#include <libutils/type/coord.h>

#include "button.h"
#include "joystick.h"

namespace mica
{

class Controller
{
public:
	struct Config
	{
		std::unique_ptr<Joystick> joystick;
		std::unique_ptr<Button> buttons[2];
	};

	explicit Controller(const Config &config);

	/**
	 * Return the position of the joystick
	 *
	 * @return
	 * @see Joystick::getPosition()
	 */
	utils::type::Coord getJoystickPosition() const
	{
		return m_joystick->getPosition();
	}

	bool isButtonDown(const int which) const
	{
		assert(which < 2);
		return m_buttons[which]->isDown();
	}

private:
	std::unique_ptr<Joystick> m_joystick;
	std::unique_ptr<Button> m_buttons[2];
};

}
