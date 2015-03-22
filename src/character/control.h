/*
 * control.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

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
 * The controller for each character
 */
class Control
{
public:
	virtual ~Control()
	{}

	virtual void control(Character *character) = 0;
};

}
}
