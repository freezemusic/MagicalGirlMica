#pragma once

#include "cocos2d_wrapper.h"
USING_NS_CC;

namespace mica
{

class Background : public Sprite
{
public:
	virtual bool init(const char *bg);

	static Background* create(const char *bg);

private:
	Sprite* bg;
};

}
