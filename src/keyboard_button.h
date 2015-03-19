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

namespace mica
{

class Context;

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

	KeyboardButton(const Context &context, const Config &config);
	virtual ~KeyboardButton();

	bool isDown() const override
	{
		return m_is_pressed;
	}

protected:
	explicit KeyboardButton(const Context &context);

	bool init(const Config &config);
	void uninit();

	const Context& getContext() const
	{
		return m_context;
	}

private:
	bool initListener();

	const Context &m_context;
	cocos2d::EventKeyboard::KeyCode m_key;
	bool m_is_pressed;
};

}
