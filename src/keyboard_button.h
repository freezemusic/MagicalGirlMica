/*
 * keyboard_button.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <base/CCEventKeyboard.h>

#include <libutils/type/coord.h>

#include "button.h"

namespace cocos2d
{

class EventListenerKeyboard;

}

namespace mica
{

class KeyboardButton : public Button
{
public:
	struct Config
	{
		cocos2d::EventKeyboard::KeyCode key;
	};

	explicit KeyboardButton(const Config &config);
	virtual ~KeyboardButton();

	bool isDown() const override
	{
		return m_is_pressed;
	}

protected:
	KeyboardButton();

	bool init(const Config &config);
	void uninit();

private:
	bool initListener();

	cocos2d::EventKeyboard::KeyCode m_key;
	bool m_is_pressed;

	cocos2d::EventListenerKeyboard *m_listener;
};

}
