/*
 * notification_manager.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <deque>
#include <functional>
#include <memory>

#include <2d/CCNode.h>
#include <base/CCDirector.h>
#include <base/CCEventDispatcher.h>

#include "event_stage_scene.h"
#include "log.h"
#include "notification.h"
#include "notification_manager.h"
#include "res.h"

#define NS_TAG "mica::"
#define TAG NS_TAG "NotificationManager::"

using namespace cocos2d;
using namespace std;

namespace mica
{

NotificationManager::NotificationManager()
		: m_is_active(false),
		  m_is_no_screen(true),
		  m_view(Node::create()),
		  m_scene_listener(nullptr)
{
	m_view->retain();
	initSceneListener();

	if (Director::getInstance()->getRunningScene())
	{
		Director::getInstance()->getRunningScene()->addChild(m_view,
				Res::kNotificationZ);
		m_is_no_screen = false;
	}
}

NotificationManager::~NotificationManager()
{
	if (m_scene_listener)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(
				m_scene_listener);
		m_scene_listener->release();
		m_scene_listener = nullptr;
	}

	m_view->removeFromParent();
	m_view->release();
}

void NotificationManager::initSceneListener()
{
	m_scene_listener = EventStageScene::Listener::create();
	m_scene_listener->retain();

	m_scene_listener->onLostFocus = [this](Scene *scene, Event*)
			{
				scene->removeChild(m_view);
				m_is_no_screen = true;
			};

	m_scene_listener->onGainFocus = [this](Scene *scene, Event*)
			{
				scene->addChild(m_view, Res::kNotificationZ);
				m_is_no_screen = false;
				if (m_is_active)
				{
					showNext();
				}
			};

	Director::getInstance()->getEventDispatcher()
			->addEventListenerWithFixedPriority(m_scene_listener,
					Res::kControlEventPriority);
}

void NotificationManager::addNotifiction(unique_ptr<Notification> &&notification)
{
	m_queue.push_back(std::move(notification));
	if (!m_is_active && !m_is_no_screen)
	{
		showNext();
	}
}

void NotificationManager::next()
{
	if (m_queue.empty())
	{
		LOG_E(TAG "next", "Empty queue");
		return;
	}

	m_queue.pop_front();
	if (m_queue.empty())
	{
		m_is_active = false;
	}
	else if (!m_is_no_screen)
	{
		showNext();
	}
}

void NotificationManager::showNext()
{
	Notification *n = m_queue.front().get();
	m_view->addChild(n->getView());
	n->setOnDismissListener(std::bind(&NotificationManager::next, this));
	m_is_active = true;
}

}
