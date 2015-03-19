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

	ResManager* getResManager() const override
	{
		return m_res_manager.get();
	}

private:
	NotificationManager* getNotificationManager_() const;

	std::unique_ptr<ResManager> m_res_manager;
	// For lazy init
	mutable std::unique_ptr<NotificationManager> m_notification_manager;
};

}
