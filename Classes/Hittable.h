#pragma once

#include "Interactable.h"

class Hittable : public Interactable
{
public:
	virtual void interactable()
	{
		m_iType = INTERACT_HIT;
	}

};
