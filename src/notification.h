/*
 * notification.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

namespace cocos2d
{

class Node;

}

namespace mica
{

/**
 * Notify user with different information
 */
class Notification
{
public:
	typedef std::function<void(void)> DismissListener;

	virtual ~Notification()
	{}

	virtual cocos2d::Node* getView() = 0;

	void setOnDismissListener(const DismissListener &listener)
	{
		m_listener = listener;
	}

protected:
	void invokeOnDismissListener()
	{
		m_listener();
	}

private:
	DismissListener m_listener;
};

}
