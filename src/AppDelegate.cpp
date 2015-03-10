#include "cocos2d_wrapper.h"

#include "AppDelegate.h"

#include <vector>
#include <string>

#include "res_manager.h"
#include "World.h"

USING_NS_CC;
using namespace std;

namespace mica
{

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Cpp Empty Test");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 \
		|| CC_TARGET_PLATFORM == CC_PLATFORM_LINUX \
		|| CC_TARGET_PLATFORM == CC_PLATFORM_MAC
        glview->setFrameSize(ResManager::getDesignW(), ResManager::getDesignH());
#endif
        director->setOpenGLView(glview);
    }

	//cocos2d::Size designResolutionSize = cocos2d::Size(1024, 480);

    director->setOpenGLView(glview);
	glview->setDesignResolutionSize(ResManager::getDesignW(),
			ResManager::getDesignH(), ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = World::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

}