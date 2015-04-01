/*
 * context_impl.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>

#include "context.h"

namespace mica
{

class NotificationManager;
class ResManager;

namespace input
{

class KeyboardManager;

}
}

namespace mica
{

/**
 * The normal implementation of Context
 */
class ContextImpl : public Context
{
public:
	ContextImpl();
	virtual ~ContextImpl();

	input::KeyboardManager* getKeyboardManager() const override
	{
		return getKeyboardManager_();
	}

	NotificationManager* getNotificationManager() const override
	{
		return getNotificationManager_();
	}

	ResManager* getResManager() const override
	{
		return m_res_manager.get();
	}

private:
	input::KeyboardManager* getKeyboardManager_() const;
	NotificationManager* getNotificationManager_() const;

	std::unique_ptr<ResManager> m_res_manager;
	// For lazy init
	mutable std::unique_ptr<NotificationManager> m_notification_manager;
	// For lazy init
	mutable std::unique_ptr<input::KeyboardManager> m_keyboard_manager;
};

}
