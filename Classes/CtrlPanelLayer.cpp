#include "CtrlPanelLayer.h"

USING_NS_CC;

CtrlPanelLayer::CtrlPanelLayer() 
{
}


bool CtrlPanelLayer::init()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	joystick = Joystick::create();
	this->addChild(joystick, 1);

	attackBtn = ButtonX::create("attackBtn.png", ButtonInputHandler::BUTTON_TYPE::BUTTON_X);
	//attackBtn->setPosition(Vec2(origin.x + visibleSize.width - 50, origin.y + 50));
	this->addChild(attackBtn, 1);


	return true;
}

void CtrlPanelLayer::update(float dt)
{

}