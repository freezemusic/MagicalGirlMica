#pragma once

#include <string>

#include <2d/CCNode.h>

#include "hittable.h"

namespace cocostudio
{

class Armature;

}

namespace mica
{

class Character : public Hittable, public cocos2d::Node
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
		kInjured,
		kTurn,
		kDie,
		kJump,
		kAttack,
		kSkill,
	};

	Status m_stat;

	int m_speed;
	cocostudio::Armature *m_arm;

	bool directToR;
};

}
