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

class MgirlMica final : public cocos2d::Application
{
public:
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

	std::unique_ptr<Controller> m_controller;
	std::stack<std::unique_ptr<Stage>> m_stages;
};

}
