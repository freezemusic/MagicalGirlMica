#pragma once

#include <string>

#include "Character.h"
#include "Interactable.h"

namespace mica
{

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

}
