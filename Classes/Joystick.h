#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "cocos2d.h"

enum class JoystickEventType{JET_TOUCH_BEGIN,JET_TOUCH_MOVE,JET_TOUCH_END};

typedef void (cocos2d::Ref::*SEL_JoystickEvent)(float interval,float x, float y,JoystickEventType type);
#define joystickEvent_selector(_SELECTOR) (SEL_JoystickEvent)(&_SELECTOR)

typedef std::function<void(float interval,float x, float y,JoystickEventType type)> JoystickEventCallback;
#define JOYSTICK_CALLBACK(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, ##__VA_ARGS__)

class Joystick : public cocos2d::Node
{
public:
	Joystick():m_bMove(false){}
	virtual ~Joystick(){}


	static Joystick* create();
	static Joystick* create(const char *fnBg,     float bgRadius,
					        const char *fnHandle, float handleRadius);

	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	void setHandleEventListener(cocos2d::Ref *target, SEL_JoystickEvent selector);
	void setHandleEventListener(JoystickEventCallback eventCallback);
	void callHandleEvent(float interval);
protected:
	cocos2d::Sprite* m_bg;
	cocos2d::Sprite* m_handle;
	bool spriteMode;

	float m_bgRadius;
	float m_handleRadius;
	bool  m_bMove;

	cocos2d::Point m_handlePos;

	JoystickEventCallback m_eventCallback;

	cocos2d::Ref*     m_touchEventListener;
    SEL_JoystickEvent m_touchEventSelector;


	bool init();
	bool init(const char *fnBg,     float bgRadius,
			  const char *fnHandle, float handleRadius);
	void initFunc();
	
};

inline void Joystick::setHandleEventListener(JoystickEventCallback eventCallback)
{
	m_eventCallback = eventCallback;
}

inline void Joystick::setHandleEventListener(cocos2d::Ref *target, SEL_JoystickEvent selector)
{
	m_touchEventListener = target;
	m_touchEventSelector = selector;
}

#endif