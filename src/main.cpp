/*
 * main.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <ctime>

#include <fstream>
#include <memory>

#include <platform/CCApplication.h>

#include <libutils/io/js_html_log_strategy.h>
#include <libutils/io/logger.h>
#include <libutils/io/system_log.h>
#include <libutils/str/str_utils.h>

#include "AppDelegate.h"
#include "log.h"

using namespace std;
using namespace utils::io;

#if __linux__
int main()
{
#if !NO_LOG
	LOG.SetLogStrategy(make_unique<JsHtmlLogStrategy<char>>(
			new ofstream(utils::str::StrUtils::Concat("log-", time(nullptr),
					".html"))));
#endif

    // create the application instance
    mica::AppDelegate app;
    return cocos2d::Application::getInstance()->run();
}

#endif
