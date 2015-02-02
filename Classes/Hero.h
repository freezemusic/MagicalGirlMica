#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Role.h"
#include "Joystick.h"

class Hero : public Role
{
public:
	Hero();

	static Hero* create(const std::string& name);
	virtual bool init(const std::string& name);

	void setControlable(bool b);
	
	virtual void response(float interval, float x, float y, JoystickEventType type);
};

#endif // __HERO_H__