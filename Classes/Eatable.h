#ifndef __EATABLE_H__
#define __EATABLE_H__

#include "Interactable.h" 

class Eatable : public Interactable
{
public:
	virtual void interactable()
	{
		m_iType = INTERACT_EAT;
	}
};

#endif // __EATABLE_H__