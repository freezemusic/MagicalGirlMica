#ifndef __WORLD_H__  
#define __WORLD_H__  

#include "cocos2d.h"
#include "Box2D/Box2D.h"  
#include "GLES-Render.h"
#include "AppMacros.h"

USING_NS_CC;

class World : public Layer
{
public:
	World();
	~World();

	//virtual bool init();
	//static cocos2d::Scene* createScene();
	//CREATE_FUNC(World);

	void setDebug(bool isDebug);
	void onDraw();
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	virtual void createBound(float width, float height);

protected:
	b2World* m_world;
	GLESDebugDraw* mDebugDraw;
	kmMat4 _modelViewMV;
	CustomCommand _customCommand;

	Size visibleSize;
	Point origin;
};

#endif // __WORLD_H__