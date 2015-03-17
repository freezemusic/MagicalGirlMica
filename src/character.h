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
	enum ROLE_STAT{
		ROLE_STAND,
		ROLE_WALK,
		ROLE_INJURED,
		ROLE_TURN,
		ROLE_DIE,
		ROLE_JUMP,
		ROLE_ATTACK,
		ROLE_SKILL,
		ROLE_NULL
	};

	Character();

	virtual void stand();
	virtual void walk(float x, float y);
	virtual void turn();
	virtual void attack();

	virtual void updateDirection();

protected:
	ROLE_STAT m_stat;

	int m_speed;
	cocostudio::Armature *m_arm;

	bool directToR;
};

}
