#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"
#include "Joystick.h"

class Player : public Character
{
public:
	Player();

	static Player* create(const std::string& name);
	virtual bool init(const std::string& name);

	void setControlable()
	{
		m_controlable = true;
	};

	virtual void response(float interval, float x, float y, JoystickEventType type);
};

#endif // __PLAYER_H__