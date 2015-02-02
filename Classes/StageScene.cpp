#include "StageScene.h"
#include "Misc.h"
#include "cocostudio/CocoStudio.h"
#include "BgSprite.h"

using namespace cocostudio;

USING_NS_CC;

StageScene::StageScene()
{
}


Scene* StageScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = StageScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
	/*
	b2Body* ground = NULL;
	b2BodyDef bd;
	bd.type = b2_staticBody;
	ground = m_world->CreateBody(&bd);
	b2ChainShape chain;
	b2Vec2 vs[3];
	vs[0].Set((-0.50f + 0.5) * bgSize.width / PTM_RATIO, (-0.40f + 0.5) * bgSize.height / PTM_RATIO);
	vs[1].Set((-0.35f + 0.5) * bgSize.width / PTM_RATIO, (-0.35f + 0.5) * bgSize.height / PTM_RATIO);
	vs[2].Set((-0.40f + 0.5) * bgSize.width / PTM_RATIO, (-0.43f + 0.5) * bgSize.height / PTM_RATIO);
	chain.CreateChain(vs, 3);
	b2FixtureDef fd;
	fd.friction = 1;
	fd.shape = &chain;
	ground->CreateFixture(&fd);

	b2ChainShape chain2;
	b2Vec2 vs2[3];
	vs2[0].Set((-0.35f + 0.5) * bgSize.width / PTM_RATIO, (-0.35f + 0.5) * bgSize.height / PTM_RATIO);
	vs2[1].Set((-0.18f + 0.5) * bgSize.width / PTM_RATIO, (-0.30f + 0.5) * bgSize.height / PTM_RATIO);
	vs2[2].Set((-0.24f + 0.5) * bgSize.width / PTM_RATIO, (-0.43f + 0.5) * bgSize.height / PTM_RATIO);
	chain2.CreateChain(vs2, 3);
	fd.friction = 1;
	fd.shape = &chain2;
	ground->CreateFixture(&fd);
	*/
	btnInputHandler = ButtonInputHandler::getInstance();
	btnInputHandler->setCommandToButton(new AttackCommand(), ButtonInputHandler::BUTTON_TYPE::BUTTON_X);
	
	
	ctrlPanel = CtrlPanelLayer::create();
	ctrlPanel->setPosition(Vec2(origin.x, origin.y));
	this->addChild(ctrlPanel, 1);

	fLayer = FightLayer::create(ctrlPanel);
	this->addChild(fLayer, 0);
	//this->scheduleUpdate();
	
    
    return true;
}

void StageScene::update(float dt)
{
}
/*
b2Body* StageScene::getBody()
{
	for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			// Synchronize the AtlasSprites position and rotation with the corresponding body
			return b;
		}
	}

}
*/

/*
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
*/
