#pragma once

#include "cocos2d_wrapper.h"

class Interactable
{
public:
	virtual void interact(Interactable *other) = 0;
};
