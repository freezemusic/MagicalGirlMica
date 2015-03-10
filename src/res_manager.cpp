/*
 * res_manager.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <fstream>
#include <string>

#include "res_manager.h"

using namespace std;

namespace mica
{

namespace
{

/**
 * Suffix .jpg if @a base_path exists with .jpg extension, .png otherwise.
 *
 * @param base_path
 * @return @a base_path with extension
 */
string addImageExt(const string &base_path)
{
	ifstream is(base_path + ".jpg");
	if (is)
	{
		return base_path + ".jpg";
	}
	else
	{
		return base_path + ".png";
	}
}

}

string ResManager::getBg(const string &bg_name)
{
	return addImageExt("res/bg/" + bg_name);
}

string ResManager::getCharacterArmature(const string &char_name)
{
	return "res/char/" + char_name + ".ExportJson";
}

}
