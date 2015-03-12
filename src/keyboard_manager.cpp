/*
 * keyboard_manager.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <functional>
#include <map>
#include <utility>

#include <base/CCDirector.h>
#include <base/CCEventDispatcher.h>
#include <base/CCEventKeyboard.h>
#include <base/CCEventListenerKeyboard.h>

#include "keyboard_manager.h"

using namespace cocos2d;
using namespace std;

namespace mica
{

KeyboardManager::KeyboardManager()
		: m_is_init(false),
		  m_listener(nullptr)
{}

void KeyboardManager::init()
{
	m_listener = EventListenerKeyboard::create();

	m_listener->onKeyPressed = [this](const EventKeyboard::KeyCode key, Event*)
			{
				auto it = m_map.find(key);
				if (it != m_map.cend())
				{
					it->second(true);
				}
			};

	m_listener->onKeyReleased = [this](const EventKeyboard::KeyCode key, Event*)
			{
				auto it = m_map.find(key);
				if (it != m_map.cend())
				{
					it->second(false);
				}
			};

	Director::getInstance()->getEventDispatcher()
			->addEventListenerWithFixedPriority(m_listener, 1);
	m_is_init = true;
}

void KeyboardManager::uninit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(
			m_listener);
	m_listener = nullptr;
	m_is_init = false;
}

void KeyboardManager::addListener(const EventKeyboard::KeyCode key,
		const Listener &listener)
{
	m_map.insert(make_pair(key, listener));
	if (!m_is_init)
	{
		init();
	}
}

void KeyboardManager::removeListener(const EventKeyboard::KeyCode key)
{
	m_map.erase(key);
	if (m_map.empty())
	{
		uninit();
	}
}

}
