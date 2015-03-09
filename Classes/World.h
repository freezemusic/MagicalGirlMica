#pragma once

#include "cocos2d_wrapper.h"
//#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "AppMacros.h"

#include "VisibleRect.h"

#include "Background.h"
#include "Player.h"

USING_NS_CC;

namespace mica
{

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

}
