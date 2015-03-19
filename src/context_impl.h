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

class KeyboardManager;
class NotificationManager;
class ResManager;

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

	KeyboardManager* getKeyboardManager() const override
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
	KeyboardManager* getKeyboardManager_() const;
	NotificationManager* getNotificationManager_() const;

	std::unique_ptr<ResManager> m_res_manager;
	// For lazy init
	mutable std::unique_ptr<NotificationManager> m_notification_manager;
	// For lazy init
	mutable std::unique_ptr<KeyboardManager> m_keyboard_manager;
};

}
