/*
 * keyboard_button.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <cassert>

#include <base/CCEventKeyboard.h>

#include "context.h"
#include "input/keyboard_button.h"
#include "input/keyboard_manager.h"

using namespace cocos2d;

namespace mica
{
namespace input
{

KeyboardButton::KeyboardButton(const Context &context)
		: m_context(context),
		  m_key(EventKeyboard::KeyCode::KEY_NONE),
		  m_is_pressed(false)
{}

KeyboardButton::KeyboardButton(const Context &context, const Config &config)
		: KeyboardButton(context)
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
		return false;
	}

	m_key = config.key;
	m_is_pressed = false;

	setGood(initListener());
	return *this;
}

bool KeyboardButton::initListener()
{
	getContext().getKeyboardManager()->addListener(m_key,
			[this](const bool is_press)
			{
				m_is_pressed = is_press;
				invokeListeners();
			});
	return true;
}

void KeyboardButton::uninit()
{
	getContext().getKeyboardManager()->removeListener(m_key);
	setGood(false);
}

}
}
