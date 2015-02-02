#include "FightLayer.h"
#include "BodyEditorLoader.h"

FightLayer::FightLayer() :m_bg(nullptr), m_ctrl(nullptr)
{
}

FightLayer::~FightLayer()
{

}


FightLayer* FightLayer::create(CtrlPanelLayer* m_ctrl)
{
	FightLayer *fLayer = new FightLayer();
	if (fLayer && fLayer->init(m_ctrl))
	{
		fLayer->autorelease();
		return fLayer;
	}
	CC_SAFE_DELETE(fLayer);
	return nullptr;
}

bool FightLayer::init(CtrlPanelLayer* m_ctrl)
{
	if (!Layer::init())
	{
		return false;
	}

	FileUtils::getInstance()->addSearchPath("../json");
	std::string str = FileUtils::getInstance()->getStringFromFile("bg.json");
	BodyEditorLoader bLoader(str);
	//BodyEditorLoader bLoader("{\"rigidBodies\":[{\"name\":\"BG\",\"imagePath\":\"Resources/bg.png\",\"origin\":{\"x\":-0.002499968046322465,\"y\":-0.004999965894967318},\"polygons\":[[{\"x\":0.8625000715255737,\"y\":0.02999994158744812},{\"x\":0.815000057220459,\"y\":0.03499993681907654},{\"x\":0.7674999833106995,\"y\":0.0274999737739563}],[{\"x\":0.6299999952316284,\"y\":0.04749998450279236},{\"x\":0.5674999952316284,\"y\":0.057499974966049194},{\"x\":0.5,\"y\":0.0549999475479126}],[{\"x\":0.5,\"y\":0.0549999475479126},{\"x\":0.45000001788139343,\"y\":0.052499979734420776},{\"x\":0.4099999964237213,\"y\":0.039999932050704956},{\"x\":0.7374999523162842,\"y\":0.02999994158744812},{\"x\":0.6875,\"y\":0.039999932050704956},{\"x\":0.6299999952316284,\"y\":0.04749998450279236}],[{\"x\":0.11750007420778275,\"y\":0.015000046230852604},{\"x\":-0.0074999635107815266,\"y\":0.022500069811940193},{\"x\":-0.004999965894967318,\"y\":-0.004999965894967318}],[{\"x\":-0.004999965894967318,\"y\":-0.004999965894967318},{\"x\":0.9999999403953552,\"y\":-0.004999965894967318},{\"x\":0.7674999833106995,\"y\":0.0274999737739563},{\"x\":0.7374999523162842,\"y\":0.02999994158744812},{\"x\":0.27000001072883606,\"y\":0.02249997854232788},{\"x\":0.11750007420778275,\"y\":0.015000046230852604}],[{\"x\":0.7374999523162842,\"y\":0.02999994158744812},{\"x\":0.4099999964237213,\"y\":0.039999932050704956},{\"x\":0.34999996423721313,\"y\":0.039999932050704956},{\"x\":0.27000001072883606,\"y\":0.02249997854232788}],[{\"x\":0.9999999403953552,\"y\":-0.004999965894967318},{\"x\":0.9099999070167542,\"y\":0.025000067427754402},{\"x\":0.8625000715255737,\"y\":0.02999994158744812},{\"x\":0.7674999833106995,\"y\":0.0274999737739563}],[{\"x\":0.9999999403953552,\"y\":-0.004999965894967318},{\"x\":1,\"y\":0.024999946355819702},{\"x\":0.9524999856948853,\"y\":0.03250003233551979},{\"x\":0.9099999070167542,\"y\":0.025000067427754402}]],\"circles\":[],\"shapes\":[{\"type\":\"POLYGON\",\"vertices\":[{\"x\":-0.004999965894967318,\"y\":-0.004999965894967318},{\"x\":-0.0074999635107815266,\"y\":0.022500069811940193},{\"x\":0.11750007420778275,\"y\":0.015000046230852604},{\"x\":0.27000001072883606,\"y\":0.02249997854232788},{\"x\":0.34999996423721313,\"y\":0.039999932050704956},{\"x\":0.4099999964237213,\"y\":0.039999932050704956},{\"x\":0.45000001788139343,\"y\":0.052499979734420776},{\"x\":0.5,\"y\":0.0549999475479126},{\"x\":0.5674999952316284,\"y\":0.057499974966049194},{\"x\":0.6299999952316284,\"y\":0.04749998450279236},{\"x\":0.6875,\"y\":0.039999932050704956},{\"x\":0.7374999523162842,\"y\":0.02999994158744812},{\"x\":0.7674999833106995,\"y\":0.0274999737739563},{\"x\":0.815000057220459,\"y\":0.03499993681907654},{\"x\":0.8625000715255737,\"y\":0.02999994158744812},{\"x\":0.9099999070167542,\"y\":0.025000067427754402},{\"x\":0.9524999856948853,\"y\":0.03250003233551979},{\"x\":1,\"y\":0.024999946355819702},{\"x\":0.9999999403953552,\"y\":-0.004999965894967318}]}]}],\"dynamicObjects\":[]}");
	b2BodyDef bdbg;
	bdbg.type = b2_staticBody;
	b2FixtureDef bfbg;
	bfbg.friction = 1.0f;
	b2Body* bodybg = m_world->CreateBody(&bdbg);
	bLoader.attachFixture(bodybg, "BG", &bfbg, 60.0f);

	this->m_ctrl = m_ctrl;
	
	m_bg = BgSprite::create("bg.png");
	bgSize = m_bg->getContentSize();
	createBound(bgSize.width, bgSize.height);
	this->addChild(m_bg, -1);
	
	ArmatureDataManager::getInstance()->addArmatureFileInfo("NewAnimation0.png", "NewAnimation0.plist", "NewAnimation.ExportJson");
	hero = Hero::create("NewAnimation");
	hero->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(hero, 1);
	this->runAction(Follow::create(hero, Rect(0, 0, bgSize.width, visibleSize.height)));

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = hero;
	bodyDef.position.Set(visibleSize.width / 2 / PTM_RATIO, visibleSize.height / 2 / PTM_RATIO);
	b2Body* body = m_world->CreateBody(&bodyDef);
	b2PolygonShape shape1;
	shape1.SetAsBox(hero->getContentSize().width / 2 / PTM_RATIO, hero->getContentSize().height / 2 / PTM_RATIO);
	b2FixtureDef fixDef;
	fixDef.shape = &shape1;
	body->CreateFixture(&fixDef);
	hero->setPhysicsBody(body);

	auto j = m_ctrl->getJoystick();
	j->setHandleEventListener(JOYSTICK_CALLBACK(Hero::response, hero));
	/*
	this->setCameraMask(2);
	cam = Camera::create();
	cam->setCameraFlag(CameraFlag::USER1);
	this->addChild(cam);
	Vec3 eyePosOld= cam->getPosition3D();
	Vec3 rolePos = role->getPosition3D();
	Vec3 eyePos = Vec3(eyePosOld.x, eyePosOld.y, eyePosOld.z);
	CCLOG("x: %.2f y: %.2f z: %.2f", eyePosOld.x, eyePosOld.y, eyePosOld.z);
	CCLOG("x: %.2f y: %.2f z: %.2f", rolePos.x, rolePos.y, rolePos.z);
	cam->setPosition3D(Vec3(rolePos.x, eyePosOld.y, eyePosOld.z));
	cam->lookAt(Vec3(rolePos.x, eyePosOld.y, 0), Vec3(0, 1, 0));
	*/
	
	//runAction(ScaleTo::create(1.0f, 1.3f));
	
	this->scheduleUpdate();

	return true;
}

void FightLayer::update(float dt)
{
	int velocityIterat = 8;
	int positionIterat = 1;
	m_world->Step(dt, velocityIterat, positionIterat);

	b2Body* b = hero->getPhysicsBody();

	hero->setPosition(Point(b->GetPosition().x*PTM_RATIO, b->GetPosition().y*PTM_RATIO));

	ActionCommand* command = ButtonInputHandler::getInstance()->handleInput();
	if (command)
	{
		command->execute(hero);
	}
	/*
	Vec3 eyePosOld = cam->getPosition3D();
	Vec3 rolePos = role->getPosition3D();
	//if (rolePos.x > )
	float tempDiff1 = eyePosOld.y - rolePos.y;
	float tempDiff2 = eyePosOld.z - 340;
	float da;
	da = tempDiff1 / tempDiff2;

	if (eyePosOld.z > 340 && eyePosOld.y > rolePos.y){
		cam->setPosition3D(Vec3(rolePos.x, eyePosOld.y - da, eyePosOld.z - 1));
	}else{
		cam->setPosition3D(Vec3(rolePos.x, rolePos.y, eyePosOld.z));
		cam->lookAt(Vec3(rolePos.x, rolePos.y, 0), Vec3(0, 1, 0));
	}
	*/
	//this->runAction(Follow::create(role, Rect(0, 0, bgSize.width, visibleSize.height)));
	
}