#pragma once

#include "cocos2d_wrapper.h"

namespace mica
{

class Interactable
{
public:
	virtual void interact(Interactable *other) = 0;
};

}
