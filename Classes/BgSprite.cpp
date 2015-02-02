#include "BgSprite.h"

BgSprite::BgSprite() :m_bg(nullptr)
{
}

BgSprite::~BgSprite()
{

}

BgSprite* BgSprite::create(const char *bg)
{
	BgSprite *bgSprite = new BgSprite();
	if (bgSprite && bgSprite->init(bg))
	{
		bgSprite->autorelease();
		return bgSprite;
	}
	CC_SAFE_DELETE(bgSprite);
	return nullptr;
}

bool BgSprite::init(const char *bg)
{
	if (!Node::init())
	{
		return false;
	}

	m_bg = Sprite::create(bg);
	this->setContentSize(m_bg->getContentSize());
	m_bg->setAnchorPoint(Vec2(0, 0)); 
	this->addChild(m_bg,1);
	this->setAnchorPoint(Vec2(0, 0));

	return true;
}
