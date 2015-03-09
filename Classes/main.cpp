/*
 * main.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <cocos2d.h>

#include "AppDelegate.h"

#if __linux__
int main()
{
    // create the application instance
    AppDelegate app;
    return cocos2d::Application::getInstance()->run();
}

#endif
