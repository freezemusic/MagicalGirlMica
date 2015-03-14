/*
 * event_stage_scene.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <functional>
#include <string>

#include <base/CCEventCustom.h>
#include <base/CCEventListenerCustom.h>

#include "event_stage_scene.h"

using namespace cocos2d;

namespace mica
{

const std::string EventStageScene::kEventId = "mica::EventStageScene";

EventStageScene::EventStageScene(Scene *scene, const bool is_gain_focus)
		: EventCustom(kEventId),
		  m_scene(scene),
		  m_is_gain_focus(is_gain_focus)
{}

EventStageScene::Listener::Listener()
{}

bool EventStageScene::Listener::init()
{
	auto callback = [this](EventCustom* event)
			{
				EventStageScene *event_ = static_cast<EventStageScene*>(event);
				if (event_->isGainFocus())
				{
					if (onGainFocus)
					{
						onGainFocus(event_->getScene(), event_);
					}
				}
				else
				{
					if (onLostFocus)
					{
						onLostFocus(event_->getScene(), event_);
					}
				}
			};

	return EventListenerCustom::init(EventStageScene::kEventId, callback);
}

EventStageScene::Listener* EventStageScene::Listener::create()
{
	auto ret = new EventStageScene::Listener;
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

EventStageScene::Listener* EventStageScene::Listener::clone()
{
	auto ret = new EventStageScene::Listener;
	if (ret && ret->init())
	{
		ret->autorelease();
		ret->onLostFocus = onLostFocus;
		ret->onGainFocus = onGainFocus;
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool EventStageScene::Listener::checkAvailable()
{
	return (onLostFocus || onGainFocus);
}

}
