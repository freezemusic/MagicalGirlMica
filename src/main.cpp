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

#include <libutils/io/basic_log_strategy.h>
#include <libutils/io/composite_log_strategy.h>
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
	auto log_strategy = make_unique<CompositeLogStrategy<char>>();
	log_strategy->PushStrategy(make_unique<JsHtmlLogStrategy<char>>(
			new ofstream(utils::str::StrUtils::Concat("log-", time(nullptr),
					".html"))));
	log_strategy->PushStrategy(make_unique<BasicLogStrategy<char>>(&cout, false));
	LOG.SetLogStrategy(std::move(log_strategy));
#endif

    // create the application instance
    mica::AppDelegate app;
    return cocos2d::Application::getInstance()->run();
}

#endif
