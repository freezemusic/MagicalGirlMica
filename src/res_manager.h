/*
 * res_manager.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

#include "misc_type.h"

namespace mica
{

/**
 * Manage the resource files
 */
class ResManager
{
public:
	static ResManager& get()
	{
		static ResManager instance;
		return instance;
	}

	std::string getBg(const std::string &bg_name);
	std::string getCharacterArmature(const std::string &char_name);

	static Uint getDesignW()
	{
		return 1024;
	}

	static Uint getDesignH()
	{
		return 576;
	}
};

}
