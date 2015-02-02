#ifndef __CTRLPANEL_LAYER_H__
#define __CTRLPANEL_LAYER_H__

#include "cocos2d.h"
#include "Joystick.h"
#include "ActionButton.h"

USING_NS_CC;

class CtrlPanelLayer : public cocos2d::Node
{
public:
	CtrlPanelLayer();

	virtual bool init();
	CREATE_FUNC(CtrlPanelLayer);


	Joystick* getJoystick(){
		return joystick;
	}

	void update(float dt) override;

private:
	Joystick* joystick;
	ActionButton* attackBtn;
};

#endif // __CTRLPANEL_LAYER_H__