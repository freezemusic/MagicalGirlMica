#ifndef __BACKGROUND_H__ 
#define __BACKGROUND_H__ 

#include "cocos2d.h"  
USING_NS_CC;

class Background : public Sprite
{
public:
	virtual bool init(const char *bg);

	static Background* create(const char *bg);

private:
	Sprite* bg;
};

#endif // __BACKGROUND_H__