#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player();

	static Player* create(const std::string& name);
	virtual bool init(const std::string& name);

	void interact(Interactable *other) override;

	void setControlable()
	{
		m_controlable = true;
	};
};
