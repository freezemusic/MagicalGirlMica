/*
 * controller.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <cassert>

#include <array>
#include <memory>

#include <libutils/type/coord.h>

#include "button.h"
#include "controller_utils.h"
#include "joystick.h"
#include "misc_type.h"

namespace mica
{

class Controller
{
public:
	enum struct Button
	{
		kA = 0,
		kB,
	};

	struct Config
	{
		std::unique_ptr<Joystick> joystick;
		std::unique_ptr<mica::Button> buttons[2];
	};

	explicit Controller(Config &&config);

	Uint addJoystickListener(const Joystick::Listener &listener)
	{
		return m_joystick->addListener(listener);
	}

	void removeJoystickListener(const Uint id)
	{
		m_joystick->removeListener(id);
	}

	Uint addButtonListener(const Button which,
			const mica::Button::Listener &listener)
	{
		assert(static_cast<Uint>(which) < m_buttons.size());
		return m_buttons[static_cast<Uint>(which)]->addListener(listener);
	}

	void removeButtonListener(const Button which, const Uint id)
	{
		assert(static_cast<Uint>(which) < m_buttons.size());
		m_buttons[static_cast<Uint>(which)]->removeListener(id);
	}

	/**
	 * Return the position of the joystick
	 *
	 * @param is_filter Perform deadzone filtering or not, normally you would
	 * like it to be true
	 * @return
	 * @see Joystick::getPosition()
	 */
	utils::type::Coord getJoystickPosition(const bool is_filter) const
	{
		if (is_filter)
		{
			return ControllerUtils::filterDeadzone(m_joystick->getPosition());
		}
		else
		{
			return m_joystick->getPosition();
		}
	}

	bool isButtonDown(const Button which) const
	{
		assert(static_cast<Uint>(which) < m_buttons.size());
		return m_buttons[static_cast<Uint>(which)]->isDown();
	}

private:
	std::unique_ptr<Joystick> m_joystick;
	std::array<std::unique_ptr<mica::Button>, 2> m_buttons;
};

}
