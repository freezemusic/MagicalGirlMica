/*
 * notification.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "listenable.h"

namespace cocos2d
{

class Node;

}

namespace mica
{

/**
 * Notify user with different information. Notification must go through the
 * NotificationManager and cannot be used independently. Add listeners to be
 * notified when the notification is dismissed from screen
 */
class Notification : public Listenable<Notification>
{
public:
	virtual ~Notification()
	{}

	virtual cocos2d::Node* getView() = 0;
};

}
