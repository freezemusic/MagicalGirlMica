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

class CharacterControl;
class Context;

}

namespace mica
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

	virtual void stand();
	/**
	 * Move with a specific speed factor along each axis. A 0 in both axes would
	 * result in a stop
	 *
	 * @param x Speed factor alone x-axis
	 * @param y Speed factor alone y-axis
	 */
	virtual void move(const float x, const float y);
	virtual void turn();
	virtual void attack();

	void interact(Interactable*) override;

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
};

}
