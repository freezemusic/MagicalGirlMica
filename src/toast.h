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

/**
 * A notification with a short line of text
 */
class Toast : public Notification
{
public:
	explicit Toast(const std::string &text);
	explicit Toast(std::string &&text);

	cocos2d::Node* getView() override;

private:
	void initView();

	std::string m_text;
	cocos2d::Node *m_view;
};

}
