#ifndef __FIGHT_LAYER_H__  
#define __FIGHT_LAYER_H__

#include "cocos2d.h"
#include "World.h"
#include "BgSprite.h"
#include "CtrlPanelLayer.h"
#include "Hero.h"

USING_NS_CC;

class FightLayer : public World
{
public:
	FightLayer();
	~FightLayer();

	virtual bool init(CtrlPanelLayer* m_ctrl);
	static FightLayer* create(CtrlPanelLayer* m_ctrl);

	void update(float dt) override;

private:
	Camera* cam;

	BgSprite* m_bg;
	Size bgSize;

	Hero* hero;
	CtrlPanelLayer* m_ctrl;
};

#endif // __FIGHT_LAYER_H__