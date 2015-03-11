/*
 * area_joystick.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <2d/CCActionInterval.h>
#include <2d/CCLayer.h>
#include <2d/CCNode.h>
#include <2d/CCSprite.h>
#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerTouch.h>
#include <math/Vec2.h>

#include <libutils/math/math_utils.h>
#include <libutils/type/coord.h>
#include <libutils/type/rect.h>
#include <libutils/type/rect_utils.h>

#include "area_joystick.h"
#include "log.h"
#include "misc_utils.h"
#include "res_manager.h"

using namespace cocos2d;
using namespace utils::math;
using namespace utils::type;

#define NS_TAG "mica::"
#define TAG NS_TAG "AreaJoystick::"

#define AMPLITUDE 128

namespace mica
{

AreaJoystick::AreaJoystick()
		: m_indicators{nullptr, nullptr},
		  m_is_indicator_moved(false)
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
	setGood(initView(config) && initIndicator() && initListeners());
	return *this;
}

bool AreaJoystick::initView(const Config &config)
{
	Node *view = nullptr;
	if (config.is_visible)
	{
		view = LayerGradient::create(Color4B(0, 0, 0, 0x80), Color4B(0, 0, 0, 0),
				Vec2(1, 0));
	}
	else
	{
		view = LayerColor::create(Color4B(0, 0, 0, 0), m_rect.coord.x,
				m_rect.coord.y);
	}
	if (!view)
	{
		LOG_E(TAG "initView", "Failed while LayerColor::create");
		return false;
	}

	view->setContentSize(cocos2d::Size(m_rect.size.w, m_rect.size.h));
	view->setPosition(m_rect.coord.x, m_rect.coord.y);
	setView(view);
	return true;
}

bool AreaJoystick::initIndicator()
{
	Sprite *begin = Sprite::create(ResManager::get().getSystem("joystick"));
	if (!begin)
	{
		LOG_E(TAG "initIndicator", "Failed while Sprite::create");
		return false;
	}
	begin->setOpacity(0);

	Sprite *move = Sprite::create(ResManager::get().getSystem("joystick"));
	if (!move)
	{
		LOG_E(TAG "initIndicator", "Failed while Sprite::create");
		return false;
	}
	move->setOpacity(0);

	m_indicators[0] = begin;
	getView()->addChild(m_indicators[0]);
	m_indicators[1] = move;
	getView()->addChild(m_indicators[1]);
	return true;
}

bool AreaJoystick::initListeners()
{
	auto *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	auto end_touch = [this](Touch*, Event*)
			{
				m_position = {0, 0};
				invokeOnMoveListeners();
				endIndicator();
			};

	listener->onTouchBegan = [this](Touch *touch, Event*)
			{
				const Vec2 &pt = touch->getStartLocation();
				if (RectUtils::IsInsidePx(m_rect, Coord(pt.x, pt.y)))
				{
					m_position = {0, 0};
					invokeOnMoveListeners();
					beginIndicator(pt);
					return true;
				}
				else
				{
					return false;
				}
			};

	listener->onTouchMoved = [this](Touch *touch, Event*)
			{
				updatePosition(*touch);
				invokeOnMoveListeners();
				moveIndicator(touch->getLocation());
//				LOG_V(TAG "initListeners(onTouchMoved)",
//						utils::str::StrUtils::Concat(m_position.x, ", ",
//								m_position.y));
			};

	listener->onTouchEnded = end_touch;
	listener->onTouchCancelled = end_touch;

	getView()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
			listener, getView());
	return true;
}

void AreaJoystick::uninit()
{
	setView(nullptr);
	m_indicators[0] = m_indicators[1] = nullptr;
}

void AreaJoystick::updatePosition(const Touch &touch)
{
	const Vec2 &diff = touch.getLocation() - touch.getStartLocation();
	m_position.x = MathUtils::Clamp<int>(-1000, diff.x / AMPLITUDE * 1000, 1000);
	m_position.y = MathUtils::Clamp<int>(-1000, diff.y / AMPLITUDE * 1000, 1000);
}

void AreaJoystick::beginIndicator(const Vec2 &pt)
{
	STATE_GUARD(getView(), TAG "beginIndicator", VOID);

	m_indicators[0]->runAction(FadeTo::create(0.1f, 0xC0));
	m_indicators[0]->setPosition(pt);
	m_is_indicator_moved = false;
}

void AreaJoystick::moveIndicator(const Vec2 &pt)
{
	STATE_GUARD(getView(), TAG "moveIndicator", VOID);
	if (!m_is_indicator_moved)
	{
		m_indicators[1]->runAction(FadeTo::create(0.1f, 0xC0));
		m_is_indicator_moved = true;
	}
	m_indicators[1]->setPosition(pt);
}

void AreaJoystick::endIndicator()
{
	STATE_GUARD(getView(), TAG "endIndicator", VOID);
	m_indicators[0]->runAction(FadeTo::create(0.1f, 0));
	m_indicators[1]->runAction(FadeTo::create(0.1f, 0));
}

}
