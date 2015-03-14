#pragma once

#include <2d/CCScene.h>

namespace mica
{

class StageScene : public cocos2d::Scene
{
public:
	static StageScene* create();

	void onEnterTransitionDidFinish() override;
	void onExitTransitionDidStart() override;
};

}
