/*
 * keyboard_joystick.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <algorithm>

#include <base/CCDirector.h>
#include <base/CCEventDispatcher.h>
#include <base/CCEventKeyboard.h>
#include <base/CCEventListenerKeyboard.h>

#include <libutils/math/math_utils.h>
#include <libutils/str/str_utils.h>
#include <libutils/type/coord.h>

#include "keyboard_joystick.h"
#include "log.h"

using namespace cocos2d;

#define NS_TAG "mica::"
#define TAG NS_TAG "KeyboardJoystick::"

namespace mica
{

KeyboardJoystick::KeyboardJoystick()
		: m_keys{EventKeyboard::KeyCode::KEY_NONE,
				EventKeyboard::KeyCode::KEY_NONE,
				EventKeyboard::KeyCode::KEY_NONE,
				EventKeyboard::KeyCode::KEY_NONE},
		  m_is_pressed{false, false, false, false},
		  m_modifier(1.0f),
		  m_listener(nullptr)
{
	setGood(false);
}

KeyboardJoystick::KeyboardJoystick(const Config &config)
		: KeyboardJoystick()
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

	m_keys[0] = config.up_key;
	m_keys[1] = config.down_key;
	m_keys[2] = config.left_key;
	m_keys[3] = config.right_key;
	std::fill(m_is_pressed, m_is_pressed + 4, false);
	m_modifier = utils::math::MathUtils::Clamp(0.0f, config.modifier, 1.0f);

	setGood(initListeners());
	return *this;
}

bool KeyboardJoystick::initListeners()
{
	m_listener = EventListenerKeyboard::create();

	m_listener->onKeyPressed = [this](EventKeyboard::KeyCode key, Event*)
			{
				bool is_change = false;
				for (int i = 0; i < 4; ++i)
				{
					if (m_keys[i] == key)
					{
						m_is_pressed[i] = true;
						is_change = true;
					}
				}
				if (is_change)
				{
					updatePosition();
//					LOG_V(TAG "initListeners(onKeyPressed)",
//							utils::str::StrUtils::Concat(m_position.x, ", ",
//									m_position.y));
				}
			};

	m_listener->onKeyReleased = [this](EventKeyboard::KeyCode key, Event*)
			{
				bool is_change = false;
				for (int i = 0; i < 4; ++i)
				{
					if (m_keys[i] == key)
					{
						m_is_pressed[i] = false;
						is_change = true;
					}
				}
				if (is_change)
				{
					updatePosition();
//					LOG_V(TAG "initListeners(onKeyReleased)",
//							utils::str::StrUtils::Concat(m_position.x, ", ",
//									m_position.y));
				}
			};

	Director::getInstance()->getEventDispatcher()
			->addEventListenerWithFixedPriority(m_listener, 1);
	return true;
}

void KeyboardJoystick::uninit()
{
	if (m_listener)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(
				m_listener);
		m_listener = nullptr;
	}
	setGood(false);
}

void KeyboardJoystick::updatePosition()
{
	if (m_is_pressed[0])
	{
		// Up
		m_position.y = 1000 * m_modifier;
	}
	else if (m_is_pressed[1])
	{
		// Down
		m_position.y = -1000 * m_modifier;
	}
	else
	{
		m_position.y = 0;
	}

	if (m_is_pressed[2])
	{
		// Left
		m_position.x = -1000 * m_modifier;
	}
	else if (m_is_pressed[3])
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
