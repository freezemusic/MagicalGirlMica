#pragma once

namespace mica
{

class Interactable
{
public:
	virtual void interact(Interactable *other) = 0;
};

}
