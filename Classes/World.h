#ifndef __WORLD_H__  
#define __WORLD_H__  

#include "cocos2d.h"
//#include "Box2D/Box2D.h"  
#include "GLES-Render.h"
#include "AppMacros.h"

#include "VisibleRect.h"

#include "Background.h"
#include "Player.h"

USING_NS_CC;

class World : public Layer{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(World); /// implement the "static create()" method manually  

private:
	Camera* camera;
	Background* bg;
	Player* player;
};

#endif // __WORLD_H__