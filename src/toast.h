/*
 * toast.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

#include "notification.h"

namespace cocos2d
{

class Node;

}

namespace mica
{

class Context;

}

namespace mica
{

/**
 * A notification with a short line of text
 */
class Toast : public Notification
{
public:
	Toast(const Context &context, const std::string &text);
	Toast(const Context &context, std::string &&text);

	/**
	 * Override the duration of this Toast. Normally the duration is determined
	 * by the length of the text
	 *
	 * @param time
	 */
	void overrideDuration(const float duration)
	{
		m_duration = duration;
	}

	cocos2d::Node* getView() override;

protected:
	const Context& getContext() const
	{
		return m_context;
	}

private:
	cocos2d::Node* createView();

	const Context &m_context;
	std::string m_text;
	float m_duration;
};

}
