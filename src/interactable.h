#pragma once

namespace mica
{

class Interactable
{
public:
	virtual ~Interactable()
	{}

	virtual void interact(Interactable *other) = 0;
};

}
