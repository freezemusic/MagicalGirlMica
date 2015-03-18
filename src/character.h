#pragma once

#include <string>

#include "hittable.h"

namespace cocostudio
{

class Armature;

}

namespace mica
{

class Character : public Hittable
{
public:
	Character();

	virtual void stand();
	virtual void walk(float x, float y);
	virtual void turn();
	virtual void attack();

	virtual void updateDirection();

protected:
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
