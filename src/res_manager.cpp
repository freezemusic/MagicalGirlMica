/*
 * res_manager.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <string>

#include "res_manager.h"

using namespace std;

namespace mica
{

string ResManager::getBg(const string &bg_name)
{
	return "res/bg/" + bg_name + ".png";
}

string ResManager::getCharacterArmature(const string &char_name)
{
	return "res/char/" + char_name + ".ExportJson";
}

}
