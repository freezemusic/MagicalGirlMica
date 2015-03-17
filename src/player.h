#pragma once

#include <string>

#include "character.h"

namespace mica
{

class Player : public Character
{
public:
	static Player* create(const std::string& name);
	virtual bool init(const std::string& name);
	virtual void update(float) override;

	void interact(Interactable *other) override;
};

}
