/*
 * character.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>
#include <string>

#include "dynamic_stage_object.h"
#include "hittable.h"

namespace cocostudio
{

class Armature;

}

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
	};

	Character(const Context &context, Config &&config);
	~Character();

	void interact(Interactable*) override
	{}

	virtual void stand();
	/**
	 * Move with a specific speed factor alone each axis. A 0 in both axes would
	 * result in a stop
	 *
	 * @param x Speed factor alone x-axis
	 * @param y Speed factor alone y-axis
	 */
	virtual void move(const float x, const float y);
	virtual void turn();
	virtual void attack();

	virtual void updateDirection();

protected:
	explicit Character(const Context &context);

	bool init(Config &&config);
	void uninit();

	const Context& getContext() const
	{
		return m_context;
	}

private:
	enum struct Status
	{
		kNull = 0,
		kStand,
		kWalk,
		kTurn,
		kAttack,
	};

	bool initView(const Config &config);
	bool initControl();

	const Context &m_context;
	Status m_stat;
	int m_speed;
	bool directToR;
	std::unique_ptr<CharacterControl> m_control;
};

}
