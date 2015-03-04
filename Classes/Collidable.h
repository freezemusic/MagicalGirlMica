#ifndef __COLLIDABLE_H__
#define __COLLIDABLE_H__

#include "Interactable.h" 

class Collidable : public Interactable
{
public:
	virtual void interactable()
	{
		m_iType = INTERACT_COLLISION;
	}
};

#endif // __COLLIDABLE_H__