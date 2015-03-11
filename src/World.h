#pragma once

#include <memory>

#include <2d/CCCamera.h>
#include <2d/CCLayer.h>
#include <2d/CCScene.h>
#include <cocostudio/CCArmatureDataManager.h>

#include "VisibleRect.h"

#include "Background.h"
#include "on_screen_joystick.h"
#include "Player.h"

namespace mica
{

class World : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(World); /// implement the "static create()" method manually

private:
	cocos2d::Camera* camera;
	Background* bg;
	Player* player;
	std::unique_ptr<OnScreenJoystick> m_joystick;
};

}
