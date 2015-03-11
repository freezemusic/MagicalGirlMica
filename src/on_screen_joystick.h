/*
 * on_screen_joystick.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "joystick.h"

namespace cocos2d
{

class Node;

}

namespace mica
{

/**
 * On-Screen joystick. The view is retained until replaced
 */
class OnScreenJoystick : public Joystick
{
public:
	OnScreenJoystick();
	virtual ~OnScreenJoystick();

	cocos2d::Node* getView() const
	{
		return m_view;
	}

protected:
	/**
	 * Set a view for this on-screen joystick
	 *
	 * @param view
	 */
	void setView(cocos2d::Node *view);

private:
	cocos2d::Node *m_view;
};

}
