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

	NotificationManager* getNotificationManager() const override
	{
		return getNotificationManager_();
	}

private:
	NotificationManager* getNotificationManager_() const;

	// For lazy init
	mutable std::unique_ptr<NotificationManager> m_notification_manager;
};

}
