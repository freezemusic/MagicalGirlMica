#include "ActionButton.h"


USING_NS_CC;

ActionButton::ActionButton() : btnImg(nullptr)
{
}

ActionButton::~ActionButton()
{
}

ButtonInputHandler::BUTTON_TYPE ActionButton::getButtonType()
{
	return btnType;
}

ButtonX* ButtonX::create(const std::string& image, ButtonInputHandler::BUTTON_TYPE btnType)
{
	ButtonX *aButton = new ButtonX();
	if (aButton && aButton->init(image, btnType))
	{
		aButton->autorelease();
		return aButton;
	}
	CC_SAFE_DELETE(aButton);
	return nullptr;
}

bool ButtonX::init(const std::string& image, ButtonInputHandler::BUTTON_TYPE btnType)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	this->btnType = btnType;

	btnImg = Sprite::create(image);
	addChild(btnImg, 1);
	btnImg->setOpacity(128);
	btnImg->setPosition(Vec2(origin.x + visibleSize.width - 50, origin.y + 50));
	btnInputHandler = ButtonInputHandler::getInstance();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ButtonX::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(ButtonX::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool ButtonX::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Vec2 point = pTouch->getLocation();
	if (btnImg->getBoundingBox().containsPoint(point))
	{
		btnInputHandler->btn_type = this->btnType;
		return true;
	}
	return false;
}

void ButtonX::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	CCLOG("Finish run attack");
}