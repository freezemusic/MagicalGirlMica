#include "World.h"

USING_NS_CC;

World::World()
{
	mDebugDraw = 0;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	b2Vec2 gravity(0, -9.8f);
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);

	setDebug(false);

	//createBound();
}

World::~World()
{
	delete m_world;
	if (mDebugDraw)
		delete mDebugDraw;
}

void World::setDebug(bool isDebug)
{
	if (isDebug) {
		mDebugDraw = new GLESDebugDraw(PTM_RATIO);
		m_world->SetDebugDraw(mDebugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		flags += b2Draw::e_pairBit;
		flags += b2Draw::e_centerOfMassBit;
		mDebugDraw->SetFlags(flags);

		ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);

		kmGLPushMatrix();
		onDraw();
	}
}

void World::onDraw()
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");

	Mat4 oldMV;
	oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
	m_world->DrawDebugData();
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
}

void World::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags){
	Layer::draw(renderer, transform, flags);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	_modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(World::onDraw, this);
	renderer->addCommand(&_customCommand);

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void World::createBound(float width = Director::getInstance()->getVisibleSize().width, float height = Director::getInstance()->getVisibleSize().height)
{
	// The floor
	b2Body* ground = NULL;
	b2BodyDef bd;
	ground = m_world->CreateBody(&bd);

	// The base
	b2EdgeShape shape;
	shape.Set(b2Vec2(0.1f, 0.1f), b2Vec2(width / PTM_RATIO - 0.1f, 0.1f));
	ground->CreateFixture(&shape, 0.0f);

	shape.Set(b2Vec2(0.1f, 0.1f), b2Vec2(0.1f, height / PTM_RATIO - 0.1f));
	ground->CreateFixture(&shape, 0.0f);

	shape.Set(b2Vec2(0.1f, height / PTM_RATIO - 0.1f), b2Vec2(width / PTM_RATIO - 0.1f, height / PTM_RATIO - 0.1f));
	ground->CreateFixture(&shape, 0.0f);

	shape.Set(b2Vec2(width / PTM_RATIO - 0.1f, 0.1f), b2Vec2(width / PTM_RATIO - 0.1f, height / PTM_RATIO - 0.1f));
	ground->CreateFixture(&shape, 0.0f);
}
/*
bool World::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	drawBox();

	return true;
}

Scene* World::createScene()
{
	Scene* scene = Scene::create();
	World *layer = World::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
*/