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

	explicit Character(Config &&config);
	~Character();

	void interact(Interactable*) override
	{}

	virtual void stand();
	virtual void walk(float x, float y);
	virtual void turn();
	virtual void attack();

	virtual void updateDirection();

protected:
	Character();

	bool init(Config &&config);
	void uninit();

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

	Status m_stat;
	int m_speed;
	bool directToR;
	std::unique_ptr<CharacterControl> m_control;
};

}
