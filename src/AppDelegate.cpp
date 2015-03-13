// For GLViewImpl
#include "cocos2d_wrapper.h"

#include "AppDelegate.h"
#include "log.h"
#include "res_manager.h"
#include "test_stage_scene.h"

using namespace cocos2d;
using namespace std;

#define NS_TAG "mica::"
#define TAG NS_TAG "AppDelegate::"

namespace mica
{

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	auto *director = Director::getInstance();
	GLView *glview = director->getOpenGLView();
	if (!glview)
	{
		glview = GLViewImpl::create("Cpp Empty Test");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 \
		|| CC_TARGET_PLATFORM == CC_PLATFORM_LINUX \
		|| CC_TARGET_PLATFORM == CC_PLATFORM_MAC
		glview->setFrameSize(ResManager::getDesignW(), ResManager::getDesignH());
#endif
		director->setOpenGLView(glview);
	}
	glview->setDesignResolutionSize(ResManager::getDesignW(),
			ResManager::getDesignH(), ResolutionPolicy::SHOW_ALL);

	director->setDisplayStats(true);
	// set FPS
	director->setAnimationInterval(1.0 / 60);

	// Load the test scene
	auto *scene = TestStageScene::create();
	if (!scene)
	{
		LOG_E(TAG "applicationDidFinishLaunching",
				"Failed while creating TestStageScene");
		return false;
	}

	// run
	director->runWithScene(scene);
	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

}
