#pragma once

#include <memory>

#include <platform/CCApplication.h>

namespace mica
{

class AppDelegate : public cocos2d::Application
{
public:
	void initGLContextAttrs() override;

	bool applicationDidFinishLaunching() override;
	void applicationDidEnterBackground() override;
	void applicationWillEnterForeground() override;
};

}
