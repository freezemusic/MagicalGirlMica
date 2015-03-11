/*
 * area_joystick.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <2d/CCLayer.h>
#include <2d/CCNode.h>
#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerTouch.h>

#include <libutils/type/coord.h>
#include <libutils/type/rect.h>
#include <libutils/type/rect_utils.h>

#include "area_joystick.h"
#include "log.h"
#include "res_manager.h"

using namespace cocos2d;
using namespace utils::type;

#define NS_TAG "mica::"
#define TAG NS_TAG "AreaJoystick::"

namespace mica
{

AreaJoystick::AreaJoystick()
		: m_x(0),
		  m_y(0)
{
	setGood(false);
}

AreaJoystick::AreaJoystick(const Config &config)
		: AreaJoystick()
{
	init(config);
}

AreaJoystick::~AreaJoystick()
{
	uninit();
}

bool AreaJoystick::init(const Config &config)
{
	uninit();

	m_rect = config.rect;
	setGood(initView(config) && initListeners());
	return *this;
}

bool AreaJoystick::initView(const Config &config)
{
	Node *view = LayerGradient::create(Color4B(0, 0, 0, 0x80),
			Color4B(0, 0, 0, 0), Vec2(1, 0));
	if (!view)
	{
		LOG_E(TAG "initView", "Failed while LayerColor::create");
		return false;
	}

	view->setContentSize(cocos2d::Size(m_rect.size.w, m_rect.size.h));
	view->setAnchorPoint({0.0f, 0.0f});
	view->setPosition(m_rect.coord.x, m_rect.coord.y);
	view->setVisible(config.is_visible);
	setView(view);
	return true;
}

bool AreaJoystick::initListeners()
{
	auto *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	auto reset_touch = [this](Touch*, Event*)
			{
				m_x = 0;
				m_y = 0;
				invokeOnMoveListeners();
			};
	listener->onTouchBegan = [this, reset_touch](Touch *touch, Event*)
			{
				const Vec2 &pt = touch->getStartLocation();
				if (RectUtils::IsInsidePx(m_rect, Coord(pt.x, pt.y)))
				{
					reset_touch(touch, nullptr);
					return true;
				}
				else
				{
					return false;
				}
			};
	listener->onTouchMoved = [this](Touch *touch, Event*)
			{
				const Vec2 &coord = touch->getLocation()
						- touch->getStartLocation();
				m_x = coord.x;
				m_y = coord.y;
				invokeOnMoveListeners();
//				LOG_V(TAG "initListeners(onTouchMoved)",
//						utils::str::StrUtils::Concat(m_x, ", ", m_y));
			};
	listener->onTouchEnded = reset_touch;
	listener->onTouchCancelled = reset_touch;

	getView()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
			listener, getView());
	return true;
}

void AreaJoystick::uninit()
{
	setView(nullptr);
}

}
