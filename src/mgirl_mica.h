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
	MgirlMica();
	~MgirlMica();

	void initGLContextAttrs() override;

	bool applicationDidFinishLaunching() override;
	void applicationDidEnterBackground() override;
	void applicationWillEnterForeground() override;

protected:
	const Context& getContext() const
	{
		return *m_context;
	}

private:
	void initDirector();
	void initView();
	void initController();
	bool initStage();

	std::unique_ptr<Context> m_context;

	std::stack<std::unique_ptr<Stage>> m_stages;
	std::unique_ptr<Controller> m_controller;
};

}
