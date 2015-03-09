#pragma once

#include "Hittable.h"
#include "cocostudio/CocoStudio.h"
#include "Joystick.h"

USING_NS_CC;
using namespace cocostudio;

class Character : public Hittable
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

	enum ROLE_TYPE{
		ROLE_TYPE_NULL,
		ROLE_TYPE_PLAYER,
		ROLE_TYPE_ENEMY
	};
public:
	Character();

	virtual inline bool isHittable(){ return true; }
	virtual inline int getId(){ return m_id; }
	virtual void setControlable() = 0;

public:
	virtual void stand();
	virtual void walk(float x, float y);
	virtual void turn();
	virtual void attack();

	virtual void updateDirection(float delta);

protected:
	ROLE_TYPE m_type;
	ROLE_STAT m_stat;

	int m_id;
	int m_speed;
	std::string m_name;
	Armature* m_arm;

	bool directToR;
	bool m_controlable;
};
