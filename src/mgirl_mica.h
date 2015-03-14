/*
 * mgirl_mica.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>

#include <platform/CCApplication.h>

namespace mica
{

class MgirlMica : public cocos2d::Application
{
public:
	void initGLContextAttrs() override;

	bool applicationDidFinishLaunching() override;
	void applicationDidEnterBackground() override;
	void applicationWillEnterForeground() override;
};

}
