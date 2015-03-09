#include "cocos2d_wrapper.h"

#include "Joystick.h"

USING_NS_CC;

Joystick* Joystick::create()
{
	Joystick *joystick = new Joystick();
	if (joystick && joystick->init())
	{
		joystick->autorelease();
		return joystick;
	}

	CC_SAFE_DELETE(joystick);
	return NULL;
}

Joystick* Joystick::create(const char *fnBg,float bgRadius,const char *fnHandle,float handleRadius)
{
    Joystick *joystick = new Joystick();
    if (joystick && joystick->init(fnBg,bgRadius,fnHandle,handleRadius))
    {
        joystick->autorelease();
        return joystick;
    }

    CC_SAFE_DELETE(joystick);
    return NULL;
}

bool Joystick::init()
{
	spriteMode = false;
	m_bg = Sprite::create();
	if (!m_bg)
		return false;
	this->addChild(m_bg);

	//´´½¨Ò¡¸Ë¾«Áé
	m_handle = Sprite::create();
	if (!m_handle)
		return false;
	this->addChild(m_handle);

	initFunc();

	return true;
}

bool Joystick::init(const char *fnBg,float bgRadius,const char *fnHandle,float handleRadius)
{
	//For debugging mode
	this->setVisible(false);

	spriteMode = true;
	//´´½¨µ×ÅÌ¾«Áé
	m_bg = Sprite::create(fnBg);
	if(!m_bg)
		return false;
	this->addChild(m_bg);

	//´´½¨Ò¡¸Ë¾«Áé
	m_handle = Sprite::create(fnHandle);
	if(!m_handle)
		return false;
	this->addChild(m_handle);

	initFunc();

	return true;

}

void Joystick::initFunc()
{
	//初始化参数
	m_touchEventListener = 0;
	m_touchEventSelector = 0;
	m_bgRadius = 40.0f;
	m_handleRadius = 25.0f;
	m_handlePos = Vec2(0.0f, 0.0f);

	//设置底盘的大小
	float bgDiameter = m_bgRadius * 2;
	Size oriBgSize = m_bg->getContentSize();
	m_bg->setScaleX(bgDiameter / oriBgSize.width);
	m_bg->setScaleY(bgDiameter / oriBgSize.height);

	//设置摇杆的大小
	float handleDiameter = m_handleRadius * 2;
	Size oriHandleSize = m_handle->getContentSize();
	m_handle->setScaleX(handleDiameter / oriHandleSize.width);
	m_handle->setScaleY(handleDiameter / oriHandleSize.height);

	//设置定时器
	this->schedule(schedule_selector(Joystick::callHandleEvent));

	//设置触碰触碰事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Joystick::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Joystick::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Joystick::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(Joystick::onTouchCancelled, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	return;
}

bool Joystick::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Point point = this->convertTouchToNodeSpaceAR(pTouch);

	//ÅÐ¶Ï´¥µãÊÇ·ñÔÚÒ¡¸ËÉÏ
	//if(point.x*point.x+point.y*point.y < m_handleRadius*m_handleRadius)
	if (pTouch->getLocation().x > (Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x) / 2)
		return false;
	else if(point.x*point.x+point.y*point.y > m_handleRadius*m_handleRadius)
	{
		m_bMove = true;
		this->setPosition(pTouch->getLocation());

		Point pos = m_handle->getPosition();
		if(m_touchEventListener && m_touchEventSelector)
			(m_touchEventListener->*m_touchEventSelector)(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JoystickEventType::JET_TOUCH_BEGIN);

		if(m_eventCallback)
			m_eventCallback(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JoystickEventType::JET_TOUCH_BEGIN);

		return true;
	}
	else
		return false;
}

void Joystick::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	//½«Ò¡¸ËÏÞÖÆÔÚµ×ÅÌµÄ·¶Î§ÄÚ
	Point point = this->convertTouchToNodeSpaceAR(pTouch);

	if(point.x*point.x+point.y*point.y > m_bgRadius*m_bgRadius)
	{
		point.normalize();
		point = point * m_bgRadius;
	}

	m_handle->setPosition(point);
}

void Joystick::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	Point pos = m_handle->getPosition();
	this->setPosition(m_handlePos);

	if(m_touchEventListener && m_touchEventSelector)
			(m_touchEventListener->*m_touchEventSelector)(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JoystickEventType::JET_TOUCH_END);

	if(m_eventCallback)
		m_eventCallback(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JoystickEventType::JET_TOUCH_END);

	m_handle->setPosition(Vec2(0.0f,0.0f));

	m_bMove = false;
}

void Joystick::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
	Point pos = m_handle->getPosition();

	if(m_touchEventListener && m_touchEventSelector)
			(m_touchEventListener->*m_touchEventSelector)(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JoystickEventType::JET_TOUCH_END);

	if(m_eventCallback)
		m_eventCallback(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JoystickEventType::JET_TOUCH_END);

	m_handle->setPosition(Vec2(0.0f,0.0f));

	m_bMove = false;
}

void Joystick::callHandleEvent(float interval)
{
	if(m_bMove)
	{
		//µ÷ÓÃÒ¡¸ËÊÂ¼þ´¦Àí·½·¨
		Point point = m_handle->getPosition();

		if(m_touchEventListener && m_touchEventSelector)
			(m_touchEventListener->*m_touchEventSelector)(interval,point.x/m_bgRadius,point.y/m_bgRadius,JoystickEventType::JET_TOUCH_MOVE);

		if(m_eventCallback)
			m_eventCallback(interval,point.x/m_bgRadius,point.y/m_bgRadius,JoystickEventType::JET_TOUCH_MOVE);
	}
}
