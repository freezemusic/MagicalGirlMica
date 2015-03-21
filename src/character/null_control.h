/*
 * null_control.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "character/control.h"

namespace mica
{
namespace character
{

class Character;

}
}

namespace mica
{
namespace character
{

/**
 * A CharacterControl that could only tell the Character to stand
 */
class NullControl : public Control
{
public:
	void control(Character *character) override;
};

}
}
