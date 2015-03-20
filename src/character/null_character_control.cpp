/*
 * null_character_control.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include "character.h"
#include "character_control.h"
#include "null_character_control.h"

namespace mica
{

void NullCharacterControl::control(Character *character)
{
	character->move(0, 0);
}

}
