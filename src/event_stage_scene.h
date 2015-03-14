/*
 * event_stage_scene.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <functional>
#include <string>

#include <base/CCEventCustom.h>
#include <base/CCEventListenerCustom.h>

namespace cocos2d
{

class Scene;

}

namespace mica
{

/**
 * Scene event triggered by StageScene
 */
class EventStageScene : public cocos2d::EventCustom
{
public:
	class Listener : public cocos2d::EventListenerCustom
	{
	public:
		static Listener* create();

		virtual Listener* clone() override;
		virtual bool checkAvailable() override;

		/**
		 * Call when @a scene is about to, i.e. before, lose focus. More
		 * specifically, during StageScene::onExitTransitionDidStart()
		 */
		std::function<void(cocos2d::Scene *scene, Event *event)> onLostFocus;
		/**
		 * Call when @a scene is about to, i.e. before, gain focus. More
		 * specifically, during StageScene::onEnterTransitionDidFinish()
		 */
		std::function<void(cocos2d::Scene *scene, Event *event)> onGainFocus;

	protected:
		Listener();

		bool init();
	};

	static const std::string kEventId;

	EventStageScene(cocos2d::Scene *scene, const bool is_gain_focus);

	cocos2d::Scene* getScene() const
	{
		return m_scene;
	}

	bool isGainFocus() const
	{
		return m_is_gain_focus;
	}

private:
	cocos2d::Scene *m_scene;
	bool m_is_gain_focus;
};

}
