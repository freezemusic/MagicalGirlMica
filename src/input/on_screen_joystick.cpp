/*
 * on_screen_joystick.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <2d/CCNode.h>
#include <base/CCEventDispatcher.h>

#include "input/on_screen_joystick.h"

using namespace cocos2d;

namespace mica
{
namespace input
{

OnScreenJoystick::OnScreenJoystick(const Context &context)
		: m_context(context),
		  m_view(nullptr)
{}

OnScreenJoystick::~OnScreenJoystick()
{
	setView(nullptr);
}

void OnScreenJoystick::setView(Node *view)
{
	if (m_view)
	{
		m_view->getEventDispatcher()->removeEventListenersForTarget(m_view);
		m_view->removeFromParent();
		m_view->release();
	}
	m_view = view;
	if (m_view)
	{
		m_view->retain();
		setGood(true);
	}
	else
	{
		setGood(false);
	}
}

}
}
