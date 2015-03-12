/*
 * keyboard_button.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <cassert>

#include <base/CCDirector.h>
#include <base/CCEventDispatcher.h>
#include <base/CCEventKeyboard.h>
#include <base/CCEventListenerKeyboard.h>

#include "keyboard_button.h"

using namespace cocos2d;

namespace mica
{

KeyboardButton::KeyboardButton()
		: m_key(EventKeyboard::KeyCode::KEY_NONE),
		  m_is_pressed(false),
		  m_listener(nullptr)
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
	assert(config.key != EventKeyboard::KeyCode::KEY_NONE);

	uninit();

	m_key = config.key;
	m_is_pressed = false;

	setGood(initListener());
	return *this;
}

bool KeyboardButton::initListener()
{
	m_listener = EventListenerKeyboard::create();

	m_listener->onKeyPressed = [this](EventKeyboard::KeyCode key, Event*)
			{
				if (m_key == key)
				{
					m_is_pressed = true;
					invokeListeners();
				}
			};

	m_listener->onKeyReleased = [this](EventKeyboard::KeyCode key, Event*)
			{
				if (m_key == key)
				{
					m_is_pressed = false;
					invokeListeners();
				}
			};

	Director::getInstance()->getEventDispatcher()
			->addEventListenerWithFixedPriority(m_listener, 1);
	return true;
}

void KeyboardButton::uninit()
{
	if (m_listener)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(
				m_listener);
		m_listener = nullptr;
	}
	setGood(false);
}

}
