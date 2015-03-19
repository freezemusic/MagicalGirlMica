/*
 * keyboard_joystick.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <array>
#include <memory>

#include <base/CCEventKeyboard.h>

#include <libutils/type/coord.h>

#include "joystick.h"
#include "keyboard_button.h"

namespace mica
{

class KeyboardManager;

}

namespace mica
{

/**
 * Using keyboard to emulate a joystick, since there's no half pressed state for
 * a key, the joystick position will simply be either 0 or max
 */
class KeyboardJoystick : public Joystick
{
public:
	struct Config
	{
		KeyboardManager *keyboard_manager;
		/// @{
		/**
		 * Map the joystick keys to different keycodes
		 */
		cocos2d::EventKeyboard::KeyCode up_key =
				cocos2d::EventKeyboard::KeyCode::KEY_W;
		cocos2d::EventKeyboard::KeyCode down_key =
				cocos2d::EventKeyboard::KeyCode::KEY_S;
		cocos2d::EventKeyboard::KeyCode left_key =
				cocos2d::EventKeyboard::KeyCode::KEY_A;
		cocos2d::EventKeyboard::KeyCode right_key =
				cocos2d::EventKeyboard::KeyCode::KEY_D;
		/// @}
		/**
		 * Modify this value to change the returned position when a key is
		 * pressed (e.g., set to 0.8 the returned position would be max * 0.8)
		 */
		float modifier = 1.0f;
	};

	explicit KeyboardJoystick(const Config &config);
	virtual ~KeyboardJoystick();

	utils::type::Coord getPosition() const override
	{
		return m_position;
	}

protected:
	KeyboardJoystick();

	bool init(const Config &config);
	void uninit();

private:
	bool initButtons(const Config &config);

	void updatePosition();

	utils::type::Coord m_position;

	// up, down, left, right
	std::array<std::unique_ptr<KeyboardButton>, 4> m_btns;
	float m_modifier;
};

}
