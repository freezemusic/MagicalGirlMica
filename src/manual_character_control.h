/*
 * manual_character_control.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "character_control.h"

namespace mica
{

class Character;
class Controller;

}

namespace mica
{

/**
 * A CharacterControl that connects with the Controller
 */
class ManualCharacterControl : public CharacterControl
{
public:
	struct Config
	{
		Controller *controller;
	};

	explicit ManualCharacterControl(const Config &config);

	void control(Character *character) override;

private:
	Controller *m_controller;
};

}
