#include "cocos2d_wrapper.h"

#include "Background.h"

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

	auto m_bg = this->bg;
	m_bg = Sprite::create(bg);
	m_bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_bg);

	return true;
}

}
