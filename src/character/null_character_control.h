/*
 * null_character_control.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "character_control.h"

namespace mica
{

class Character;

}

namespace mica
{

/**
 * A CharacterControl that could only tell the Character to stand
 */
class NullCharacterControl : public CharacterControl
{
public:
	void control(Character *character) override;
};

}
