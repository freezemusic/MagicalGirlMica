#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "cocos2d.h"  
USING_NS_CC;

class BgSprite : public Node
{
public:
	BgSprite();
	~BgSprite();
	virtual bool init(const char *bg);

	static BgSprite* create(const char *bg);

private:
	Sprite* m_bg; 
};

#endif // __BACKGROUND_H__