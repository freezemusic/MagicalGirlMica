/*
 * character_control.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

namespace mica
{

class Character;

}

namespace mica
{

/**
 * The controller for each character
 */
class CharacterControl
{
public:
	virtual ~CharacterControl()
	{}

	virtual void control(Character *character) = 0;
};

}
