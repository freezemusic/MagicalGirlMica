#ifndef __COLLIDABLE_H__
#define __COLLIDABLE_H__

#include "cocos2d.h"

class Collidable
{
public:
	virtual bool isCollidable() = 0;
};

#endif // __COLLIDABLE_H__