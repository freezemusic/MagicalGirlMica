/*
 * character.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

#include "dynamic_scene_object.h"
#include "hittable.h"

namespace cocostudio
{

class Armature;

}

namespace mica
{

/**
 * Character is a controllable object moving around the scene
 */
class Character : public Hittable, public DynamicSceneObject
{
public:
	Character();

	virtual void stand();
	virtual void walk(float x, float y);
	virtual void turn();
	virtual void attack();

	virtual void updateDirection();

private:
	enum struct Status
	{
		kNull = 0,
		kStand,
		kWalk,
		kTurn,
		kAttack,
	};

	Status m_stat;

	int m_speed;
	cocostudio::Armature *m_arm;

	bool directToR;
};

}
