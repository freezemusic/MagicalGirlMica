#pragma once

#include <2d/CCCamera.h>
#include <2d/CCLayer.h>
#include <2d/CCScene.h>
#include <cocostudio/CCArmatureDataManager.h>

#include "GLES-Render.h"

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
