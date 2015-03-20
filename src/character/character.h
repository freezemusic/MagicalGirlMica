/*
 * character.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>
#include <string>

#include <libutils/type/coord.h>

#include "dynamic_stage_object.h"
#include "hittable.h"

namespace mica
{

class Context;

namespace character
{

class CharacterControl;

}
}

namespace mica
{
namespace character
{

/**
 * Character is a controllable object moving around the scene
 */
class Character : public Hittable, public DynamicStageObject
{
public:
	struct Config
	{
		std::string identifier;
		std::unique_ptr<CharacterControl> control;
		/// The initial position
		utils::type::Coord pos;
	};

	Character(const Context &context, Config &&config);
	virtual ~Character();

	/**
	 * Move with a specific speed factor along each axis. A 0 in both axes would
	 * result in a stop
	 *
	 * @param x Normalized speed factor alone x-axis, [0,1000]
	 * @param y Normalized speed factor alone y-axis, [0,1000]
	 */
	void move(const int x, const int y);
	void attack();

	void interact(Interactable*) override;

	int getEp() const
	{
		return m_ep;
	}

	void setEp(const int val)
	{
		m_ep = val;
	}

	utils::type::Coord getPosition() const
	{
		return m_position;
	}

	void setPosition(const utils::type::Coord &val)
	{
		m_position = val;
	}

protected:
	explicit Character(const Context &context);

	bool init(Config &&config);
	void uninit();

	const Context& getContext() const
	{
		return m_context;
	}

private:
	bool initView(const Config &config);
	bool initControl();

	const Context &m_context;
	std::unique_ptr<CharacterControl> m_control;

	int m_ep;
	utils::type::Coord m_position;
};

}
}
