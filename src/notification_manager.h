/*
 * notification_manager.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <deque>
#include <memory>

#include "event_stage_scene.h"

namespace cocos2d
{

class Node;

}

namespace mica
{

class Notification;

}

namespace mica
{

/**
 * Manage and show Notification on screen
 *
 * @see Notification
 */
class NotificationManager final
{
public:
	static NotificationManager& get()
	{
		static NotificationManager instance;
		return instance;
	}

	NotificationManager();
	~NotificationManager();

	/**
	 * Push a new notification to the queue to be shown some time in the future
	 *
	 * @param notification
	 */
	void addNotifiction(std::unique_ptr<Notification> &&notification);

private:
	void initSceneListener();

	void next();
	void showNext();

	std::deque<std::unique_ptr<Notification>> m_queue;
	bool m_is_active;
	bool m_is_no_screen;

	cocos2d::Node *m_view;
	EventStageScene::Listener *m_scene_listener;
};

}
