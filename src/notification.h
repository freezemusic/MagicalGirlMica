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
	virtual ~Notification()
	{}

	virtual cocos2d::Node* getView() = 0;
};

}
