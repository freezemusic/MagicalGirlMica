#pragma once

#include "cocos2d_wrapper.h"

class Interactable : public cocos2d::Node
{
public:
	enum INTERACT_TYPE
	{
		INTERACT_NULL,
		INTERACT_HIT,
		INTERACT_EAT,
		INTERACT_COLLISION
	};

	virtual void interactable() = 0;

protected:
	INTERACT_TYPE m_iType;
};
