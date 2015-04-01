/*
 * context.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

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
 * Interface to global information about an application environment. It allows
 * access to application-specific resources and classes, etc.
 */
class Context
{
public:
	virtual ~Context()
	{}

	virtual input::KeyboardManager* getKeyboardManager() const = 0;
	virtual NotificationManager* getNotificationManager() const = 0;
	virtual ResManager* getResManager() const = 0;
};

}
