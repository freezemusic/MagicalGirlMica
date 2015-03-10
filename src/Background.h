#pragma once

#include <2d/CCSprite.h>

namespace mica
{

class Background : public cocos2d::Sprite
{
public:
	virtual bool init(const char *bg);

	static Background* create(const char *bg);

private:
	cocos2d::Sprite* m_bg;
};

}
