/*
 * joystick.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <functional>
#include <list>

#include "joystick.h"

using namespace std;

Joystick::Joystick()
		: m_id(0)
{}

Joystick::~Joystick()
{}

void Joystick::addOnMoveListener(const OnMoveListener &listener)
{
	m_listeners.push_back(make_pair(m_id++, listener));
}

void Joystick::removeOnMoveListener(const Uint id)
{
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it)
	{
		if (it->first == id)
		{
			m_listeners.erase(it);
			return;
		}
	}
}

void Joystick::invokeOnMoveListeners()
{
	for (auto &l : m_listeners)
	{
		l.second(this);
	}
}
