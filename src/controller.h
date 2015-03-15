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
#include "joystick.h"
#include "misc_type.h"

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

	explicit Controller(Config &&config);

	Uint addJoystickListener(const Joystick::Listener &listener)
	{
		return m_joystick->addListener(listener);
	}

	void removeJoystickListener(const Uint id)
	{
		m_joystick->removeListener(id);
	}

	Uint addButtonListener(const Uint which, const Button::Listener &listener)
	{
		assert(which < m_buttons.size());
		return m_buttons[which]->addListener(listener);
	}

	void removeButtonListener(const Uint which, const Uint id)
	{
		assert(which < m_buttons.size());
		m_buttons[which]->removeListener(id);
	}

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

	bool isButtonDown(const Uint which) const
	{
		assert(which < m_buttons.size());
		return m_buttons[which]->isDown();
	}

private:
	std::unique_ptr<Joystick> m_joystick;
	std::array<std::unique_ptr<Button>, 2> m_buttons;
};

}
