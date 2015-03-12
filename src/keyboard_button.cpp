/*
 * keyboard_button.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <cassert>

#include <base/CCEventKeyboard.h>

#include "keyboard_button.h"
#include "keyboard_manager.h"

using namespace cocos2d;

namespace mica
{

KeyboardButton::KeyboardButton()
		: m_key(EventKeyboard::KeyCode::KEY_NONE),
		  m_is_pressed(false)
{
	setGood(false);
}

KeyboardButton::KeyboardButton(const Config &config)
		: KeyboardButton()
{
	init(config);
}

KeyboardButton::~KeyboardButton()
{
	uninit();
}

bool KeyboardButton::init(const Config &config)
{
	uninit();

	if (config.key == EventKeyboard::KeyCode::KEY_NONE)
	{
		setGood(false);
		return false;
	}

	m_key = config.key;
	m_is_pressed = false;

	setGood(initListener());
	return *this;
}

bool KeyboardButton::initListener()
{
	KeyboardManager::get().addListener(m_key, [this](const bool is_press)
			{
				m_is_pressed = is_press;
				invokeListeners();
			});
	return true;
}

void KeyboardButton::uninit()
{
	KeyboardManager::get().removeListener(m_key);
	setGood(false);
}

}
