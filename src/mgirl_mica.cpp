/*
 * mgirl_mica.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <cassert>

// For GLViewImpl
#include "cocos2d_wrapper.h"

#include "context_impl.h"
#include "input/area_joystick.h"
#include "input/controller.h"
#include "input/keyboard_button.h"
#include "input/keyboard_manager.h"
#include "log.h"
#include "mgirl_mica.h"
#include "res.h"
#include "test_stage.h"

using namespace cocos2d;
using namespace mica::input;
using namespace std;

#define NS_TAG "mica::"
#define TAG NS_TAG "MgirlMica::"

namespace mica
{

MgirlMica::MgirlMica()
		: m_context(make_unique<ContextImpl>())
{}

MgirlMica::~MgirlMica()
{}

void MgirlMica::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
	GLView::setGLContextAttrs(glContextAttrs);
}

bool MgirlMica::applicationDidFinishLaunching()
{
	initDirector();
	initView();
	initController();

	if (!initStage())
	{
		return false;
	}
	else
	{
		Director::getInstance()->runWithScene(m_stages.top()->getScene());
		return true;
	}
}

void MgirlMica::initDirector()
{
#if DEBUG
	Director::getInstance()->setDisplayStats(true);
#endif
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
		glview->setFrameSize(Res::kDesignW, Res::kDesignH);
#endif
		Director::getInstance()->setOpenGLView(glview);
	}

	glview->setDesignResolutionSize(Res::kDesignW, Res::kDesignH,
			ResolutionPolicy::SHOW_ALL);
}

void MgirlMica::initController()
{
	Controller::Config controller_conf;

	AreaJoystick::Config joystick_conf;
	joystick_conf.rect.size.w = Res::kDesignW / 2;
	joystick_conf.rect.size.h = Res::kDesignH;
	controller_conf.joystick = make_unique<AreaJoystick>(getContext(),
			joystick_conf);

	KeyboardButton::Config button_conf[2];
	button_conf[0].key = EventKeyboard::KeyCode::KEY_0;
	controller_conf.buttons[0] = make_unique<KeyboardButton>(getContext(),
			button_conf[0]);
	button_conf[1].key = EventKeyboard::KeyCode::KEY_PERIOD;
	controller_conf.buttons[1] = make_unique<KeyboardButton>(getContext(),
			button_conf[1]);

	m_controller = make_unique<Controller>(std::move(controller_conf));
}

bool MgirlMica::initStage()
{
	TestStage::Config stage_conf;
	stage_conf.controller = m_controller.get();
	auto stage = make_unique<TestStage>(getContext(), stage_conf);
	if (!*stage)
	{
		LOG_E(TAG "initStage", "Failed while creating TestStage");
		return false;
	}
	else
	{
		m_stages.push(std::move(stage));
		return true;
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
