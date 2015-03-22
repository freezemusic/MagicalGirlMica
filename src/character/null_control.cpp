/*
 * null_control.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include "character/character.h"
#include "character/control.h"
#include "character/null_control.h"

namespace mica
{
namespace character
{

void NullControl::control(Character *character)
{
	character->move(0, 0);
}

}
}
