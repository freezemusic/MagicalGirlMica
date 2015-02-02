#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__

#include "cocos2d.h"
#include "World.h"
#include "CtrlPanelLayer.h"
#include "FightLayer.h"
#include "buttonInputHandler.h"

#include "cocostudio/CocoStudio.h"

USING_NS_CC;

class StageScene : public World
{
public:
	StageScene();

	static cocos2d::Scene* createScene(); // there's no 'id' in cpp, so we recommend returning the class instance pointer  
	virtual bool init(); // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone  
	CREATE_FUNC(StageScene); /// implement the "static create()" method manually  

	void update(float dt) override;

	//b2Body* getBody();
private:
	FightLayer* fLayer;
	CtrlPanelLayer* ctrlPanel;
	ButtonInputHandler* btnInputHandler;

	Label* label;
};

#endif // __STAGESCENE_H__ 