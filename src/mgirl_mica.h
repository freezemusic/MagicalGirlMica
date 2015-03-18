/*
 * mgirl_mica.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>

#include <platform/CCApplication.h>

#include "controller.h"

namespace cocos2d
{

class Scene;

}

namespace mica
{

class MgirlMica final : public cocos2d::Application
{
public:
	void initGLContextAttrs() override;

	bool applicationDidFinishLaunching() override;
	void applicationDidEnterBackground() override;
	void applicationWillEnterForeground() override;

private:
	void initDirector();
	void initView();
	void initController();
	cocos2d::Scene* initScene();

	std::unique_ptr<Controller> m_controller;
};

}
