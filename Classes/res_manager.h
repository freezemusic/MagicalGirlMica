/*
 * res_manager.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

namespace mica
{

/**
 * Manage the resource files
 */
class ResManager
{
public:
	static std::string getBg(const std::string &bg_name);
	static std::string getCharacterArmature(const std::string &char_name);
};

}
