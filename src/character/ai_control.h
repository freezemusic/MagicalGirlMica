/*
 * ai_control.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>

#include "character/ai.h"
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

class AiControl : public Control
{
public:
	struct Config
	{
		std::unique_ptr<Ai> ai;
	};

	explicit AiControl(Config &&config)
			: m_ai(std::move(config.ai))
	{}

	void control(Character*) override
	{
		m_ai->tick();
	}

private:
	std::unique_ptr<Ai> m_ai;
};

}
}
