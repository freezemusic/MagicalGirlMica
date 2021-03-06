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
	/**
	 * Return the path for a background resource
	 *
	 * @param char_name
	 * @return
	 */
	std::string getBg(const std::string &bg_name) const;
	/**
	 * Return the path for a character armature resource
	 *
	 * @param char_name
	 * @return
	 */
	std::string getCharacterArmature(const std::string &char_name) const;
	/**
	 * Return the path for a system resource
	 *
	 * @param system_name
	 * @return
	 */
	std::string getSystem(const std::string &system_name) const;
};

}
