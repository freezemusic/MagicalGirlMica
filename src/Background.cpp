#include <2d/CCSprite.h>
#include <math/Vec2.h>

#include "Background.h"

using namespace cocos2d;

namespace mica
{

Background* Background::create(const char *bg)
{
	Background *background = new Background();
	if (background && background->init(bg))
	{
		background->autorelease();
		return background;
	}
	CC_SAFE_DELETE(background);
	return nullptr;
}

bool Background::init(const char *bg)
{
	m_bg = Sprite::create(bg);
	m_bg->setAnchorPoint(Vec2(0, 0));
	addChild(m_bg);
	return true;
}

}
