/*
 * context_impl.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <memory>

#include "context.h"
#include "context_impl.h"
#include "keyboard_manager.h"
#include "notification_manager.h"
#include "res_manager.h"

using namespace std;

namespace mica
{

ContextImpl::ContextImpl()
		: m_res_manager(make_unique<ResManager>())
{}

ContextImpl::~ContextImpl()
{}

KeyboardManager* ContextImpl::getKeyboardManager_() const
{
	if (!m_keyboard_manager)
	{
		m_keyboard_manager = make_unique<KeyboardManager>();
	}
	return m_keyboard_manager.get();
}

NotificationManager* ContextImpl::getNotificationManager_() const
{
	if (!m_notification_manager)
	{
		m_notification_manager = make_unique<NotificationManager>();
	}
	return m_notification_manager.get();
}

}
