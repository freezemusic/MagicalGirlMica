#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "Interactable.h" 

class Hittable : public Interactable
{
public:
	virtual void interactable()
	{
		m_iType = INTERACT_HIT;
	}

};

#endif // __HITTABLE_H__