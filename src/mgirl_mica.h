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
#include "stage.h"

namespace cocos2d
{

class Scene;

}

namespace mica
{

class Context;
class KeyboardManager;

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

	MgirlMica();
	~MgirlMica();

	void initGLContextAttrs() override;

	bool applicationDidFinishLaunching() override;
	void applicationDidEnterBackground() override;
	void applicationWillEnterForeground() override;

private:
	void initDirector();
	void initView();
	void initController();
	bool initStage();

	void ensureKeyboardManager();

	std::unique_ptr<Context> m_context;
	std::unique_ptr<KeyboardManager> m_keyboard_manager;

	std::stack<std::unique_ptr<Stage>> m_stages;
	std::unique_ptr<Controller> m_controller;
};

}
