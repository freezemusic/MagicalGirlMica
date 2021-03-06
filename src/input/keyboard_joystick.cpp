/*
 * keyboard_joystick.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <array>
#include <memory>

#include <libutils/math/math_utils.h>
#include <libutils/type/coord.h>

#include "input/keyboard_button.h"
#include "input/keyboard_joystick.h"
#include "log.h"
#include "misc_type.h"

using namespace std;

#define NS_TAG "mica::"
#define TAG NS_TAG "KeyboardJoystick::"

namespace mica
{
namespace input
{

KeyboardJoystick::KeyboardJoystick(const Context &context)
		: m_context(context),
		  m_modifier(1.0f)
{}

KeyboardJoystick::KeyboardJoystick(const Context &context, const Config &config)
		: KeyboardJoystick(context)
{
	init(config);
}

KeyboardJoystick::~KeyboardJoystick()
{
	uninit();
}

bool KeyboardJoystick::init(const Config &config)
{
	uninit();

	if (!config.keyboard_manager)
	{
		LOG_E(TAG "init", "keyboard_manager can't be null");
		return false;
	}
	m_modifier = utils::math::MathUtils::Clamp(0.0f, config.modifier, 1.0f);

	setGood(initButtons(config));
	return *this;
}

bool KeyboardJoystick::initButtons(const Config &config)
{
	for (Uint i = 0; i < m_btns.size(); ++i)
	{
		KeyboardButton::Config btn_conf;
		switch (i)
		{
		default:
			LOG_E(TAG "initButton", "Too many keys");
			return false;

		case 0:
			btn_conf.key = config.up_key;
			break;

		case 1:
			btn_conf.key = config.down_key;
			break;

		case 2:
			btn_conf.key = config.left_key;
			break;

		case 3:
			btn_conf.key = config.right_key;
			break;
		}
		m_btns[i] = make_unique<KeyboardButton>(getContext(), btn_conf);
		m_btns[i]->addListener([this](Button*)
				{
					updatePosition();
					invokeListeners();
				});
	}
	return true;
}

void KeyboardJoystick::uninit()
{
	for (auto &btn : m_btns)
	{
		btn.reset();
	}
	setGood(false);
}

void KeyboardJoystick::updatePosition()
{
	if (m_btns[0]->isDown())
	{
		// Up
		m_position.y = 1000 * m_modifier;
	}
	else if (m_btns[1]->isDown())
	{
		// Down
		m_position.y = -1000 * m_modifier;
	}
	else
	{
		m_position.y = 0;
	}

	if (m_btns[2]->isDown())
	{
		// Left
		m_position.x = -1000 * m_modifier;
	}
	else if (m_btns[3]->isDown())
	{
		// Right
		m_position.x = 1000 * m_modifier;
	}
	else
	{
		m_position.x = 0;
	}
}

}
}
