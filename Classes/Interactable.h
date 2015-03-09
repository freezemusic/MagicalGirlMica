#pragma once

#include "cocos2d_wrapper.h"

class Interactable : public cocos2d::Node
{
public:
	virtual void interactable() = 0;
};
