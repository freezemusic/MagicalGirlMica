/*
 * keyboard_manager.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <functional>
#include <map>

#include <base/CCEventKeyboard.h>

namespace cocos2d
{

class EventListenerKeyboard;

}

namespace mica
{

/**
 * A proxy that manage all keyboard event listeners. This way, whenever user
 * presses a key, only one listeners would be called instead of n
 */
class KeyboardManager
{
public:
	/**
	 * The listener, if it is a press event, @a is_pressed would be true,
	 * otherwise it is a release event
	 */
	typedef std::function<void(const bool is_press)> Listener;

	KeyboardManager();

	void addListener(const cocos2d::EventKeyboard::KeyCode key,
			const Listener &listener);
	void removeListener(const cocos2d::EventKeyboard::KeyCode key);

private:
	void init();
	void uninit();

	bool m_is_init;
	std::map<cocos2d::EventKeyboard::KeyCode, Listener> m_map;
	cocos2d::EventListenerKeyboard *m_listener;
};

}
