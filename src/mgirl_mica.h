/*
 * mgirl_mica.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>
#include <stack>

#include <platform/CCApplication.h>

#include "controller.h"
#include "keyboard_manager.h"
#include "notification_manager.h"
#include "stage.h"

namespace cocos2d
{

class Scene;

}

namespace mica
{

class MgirlMica final : public cocos2d::Application
{
public:
	static MgirlMica& get()
	{
		static MgirlMica instance;
		return instance;
	}

	~MgirlMica();

	void initGLContextAttrs() override;

	bool applicationDidFinishLaunching() override;
	void applicationDidEnterBackground() override;
	void applicationWillEnterForeground() override;

	KeyboardManager& getKeyboardManager()
	{
		return m_keyboard_manager;
	}

	NotificationManager& getNotificationManager()
	{
		return m_notification_manager;
	}

private:
	void initDirector();
	void initView();
	void initController();
	bool initStage();

	KeyboardManager m_keyboard_manager;
	NotificationManager m_notification_manager;

	std::stack<std::unique_ptr<Stage>> m_stages;
	std::unique_ptr<Controller> m_controller;
};

}
