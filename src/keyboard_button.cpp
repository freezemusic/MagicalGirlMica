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
#include "log.h"

using namespace cocos2d;

#define NS_TAG "mica::"
#define TAG NS_TAG "KeyboardButton::"

namespace mica
{

KeyboardButton::KeyboardButton()
		: m_keyboard_manager(nullptr),
		  m_key(EventKeyboard::KeyCode::KEY_NONE),
		  m_is_pressed(false)
{}

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

	if (!config.keyboard_manager)
	{
		LOG_E(TAG "init", "keyboard_manager can't be null");
		return false;
	}
	if (config.key == EventKeyboard::KeyCode::KEY_NONE)
	{
		return false;
	}

	m_keyboard_manager = config.keyboard_manager;
	m_key = config.key;
	m_is_pressed = false;

	setGood(initListener());
	return *this;
}

bool KeyboardButton::initListener()
{
	m_keyboard_manager->addListener(m_key, [this](const bool is_press)
			{
				m_is_pressed = is_press;
				invokeListeners();
			});
	return true;
}

void KeyboardButton::uninit()
{
	if (m_keyboard_manager)
	{
		m_keyboard_manager->removeListener(m_key);
	}
	setGood(false);
}

}
