#ifndef __ACTIONCOMMAND_H__
#define __ACTIONCOMMAND_H__

#include "Role.h"

class ActionCommand
{
public:
	ActionCommand(){};
	~ActionCommand(){};
	virtual void execute(Role* role) = 0;
};

class AttackCommand : public ActionCommand
{
public:
	virtual void execute(Role* role){
		role->attack();
	}
};

#endif // __ACTIONCOMMAND_H__ 