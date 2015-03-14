/*
 * mgirl_mica.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <cassert>

// For GLViewImpl
#include "cocos2d_wrapper.h"

#include "log.h"
#include "mgirl_mica.h"
#include "res.h"
#include "res_manager.h"
#include "test_stage_scene.h"

using namespace cocos2d;
using namespace std;

#define NS_TAG "mica::"
#define TAG NS_TAG "MgirlMica::"

namespace mica
{

void MgirlMica::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
	GLView::setGLContextAttrs(glContextAttrs);
}

bool MgirlMica::applicationDidFinishLaunching()
{
	initDirector();
	initView();

	Scene *scene = initScene();
	if (!scene)
	{
		assert(false);
		return false;
	}
	else
	{
		Director::getInstance()->runWithScene(scene);
		return true;
	}
}

void MgirlMica::initDirector()
{
	Director::getInstance()->setDisplayStats(true);
	// 60 FPS
	Director::getInstance()->setAnimationInterval(1.0 / 60.0);
}

void MgirlMica::initView()
{
	GLView *glview = Director::getInstance()->getOpenGLView();
	if (!glview)
	{
		glview = GLViewImpl::create(Res::kAppName);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 \
		|| CC_TARGET_PLATFORM == CC_PLATFORM_LINUX \
		|| CC_TARGET_PLATFORM == CC_PLATFORM_MAC
		glview->setFrameSize(ResManager::getDesignW(), ResManager::getDesignH());
#endif
		Director::getInstance()->setOpenGLView(glview);
	}

	glview->setDesignResolutionSize(ResManager::getDesignW(),
			ResManager::getDesignH(), ResolutionPolicy::SHOW_ALL);
}

Scene* MgirlMica::initScene()
{
	auto *scene = TestStageScene::create();
	if (!scene)
	{
		LOG_E(TAG "initScene", "Failed while creating TestStageScene");
		return nullptr;
	}
	else
	{
		return scene;
	}
}

void MgirlMica::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void MgirlMica::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

}
