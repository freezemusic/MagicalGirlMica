#ifndef __ACTIONBUTTON_H__
#define __ACTIONBUTTON_H__

#include "cocos2d.h"
#include "ButtonInputHandler.h"

USING_NS_CC;

class ActionButton : public Node
{
public:
	ActionButton();
	~ActionButton();

	ButtonInputHandler::BUTTON_TYPE getButtonType();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) = 0;
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent) = 0;

protected:
	Sprite* btnImg;
	ButtonInputHandler* btnInputHandler;
	ButtonInputHandler::BUTTON_TYPE btnType;
};

class ButtonX :public ActionButton
{
public:
	static ButtonX* create(const std::string& image, ButtonInputHandler::BUTTON_TYPE btnType);
	virtual bool init(const std::string& image, ButtonInputHandler::BUTTON_TYPE btnType);

	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
};

#endif // __ACTIONBUTTON_H__