#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"
#include "AppMacros.h"
#include "Collidable.h"
#include "cocostudio/CocoStudio.h"
#include "Joystick.h"

USING_NS_CC;
using namespace cocostudio;

class Role : public Node, public Collidable
{
public:
	enum ROLE_STAT{
		ROLE_STAND,
		ROLE_WALK,
		ROLE_TURN,
		ROLE_ATTACK,
		ROLE_SKILL,
		ROLE_INJURED,
		ROLE_DIE,
		ROLE_NULL
	};

	enum ROLE_TYPE{
		ROLE_TYPE_NULL,
		ROLE_TYPE_HERO,
		ROLE_TYPE_MONSTER
	};
public:
	Role();

	void setControlable(bool b);

	virtual inline bool isCollidable(){ return true; }
	virtual inline int getId(){ return m_id; }

	virtual inline void setPhysicsBody(b2Body* b2body){ physicsBody = b2body; }
	virtual inline b2Body* getPhysicsBody(){ return physicsBody; }

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

	Layer* m_layer;
	b2Body* physicsBody;

	bool directToR;
	bool m_controlable;

};

#endif // __ROLE_H__