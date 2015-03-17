/*
 * area_joystick.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <2d/CCActionInterval.h>
#include <2d/CCLayer.h>
#include <2d/CCNode.h>
#include <2d/CCScene.h>
#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerTouch.h>
#include <math/Vec2.h>

#include <libutils/math/math_utils.h>
#include <libutils/type/coord.h>
#include <libutils/type/rect.h>
#include <libutils/type/rect_utils.h>

#include "area_joystick.h"
#include "event_stage_scene.h"
#include "log.h"
#include "misc_utils.h"
#include "res.h"
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
		: m_indicators({nullptr, nullptr}),
		  m_scene_listener(nullptr)
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
	setGood(initView(config) && initIndicator() && initSceneListener()
			&& initTouchListener());

	if (Director::getInstance()->getRunningScene())
	{
		Director::getInstance()->getRunningScene()->addChild(getView(),
				Res::kOnScreenControlZ);
	}
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

	Sprite *line = Sprite::create(ResManager::get().getSystem("joystick_line"));
	if (!line)
	{
		LOG_E(TAG "initIndicator", "Failed while Sprite::create");
		return false;
	}
	line->setOpacity(0);

	m_indicators[0] = begin;
	getView()->addChild(m_indicators[0]);
	m_indicators[1] = move;
	getView()->addChild(m_indicators[1]);
	m_indicator_line = line;
	getView()->addChild(m_indicator_line);
	return true;
}

bool AreaJoystick::initSceneListener()
{
	m_scene_listener = EventStageScene::Listener::create();
	m_scene_listener->retain();

	m_scene_listener->onLostFocus = [this](Scene *scene, Event*)
			{
				scene->removeChild(getView());
			};

	m_scene_listener->onGainFocus = [this](Scene *scene, Event*)
			{
				scene->addChild(getView(), Res::kOnScreenControlZ);
			};

	Director::getInstance()->getEventDispatcher()
			->addEventListenerWithFixedPriority(m_scene_listener,
					Res::kControlEventPriority);
	return true;
}

bool AreaJoystick::initTouchListener()
{
	auto *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	auto end_touch = [this](Touch*, Event*)
			{
				m_position = {0, 0};
				invokeListeners();
				endIndicator();
			};

	listener->onTouchBegan = [this](Touch *touch, Event*)
			{
				const Vec2 &pt = touch->getStartLocation();
				if (RectUtils::IsInsidePx(m_rect, Coord(pt.x, pt.y)))
				{
					m_position = {0, 0};
					invokeListeners();
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
				invokeListeners();
				moveIndicator(touch->getStartLocation(), touch->getLocation());
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
	if (m_scene_listener)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(
				m_scene_listener);
		m_scene_listener->release();
		m_scene_listener = nullptr;
	}

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
}

void AreaJoystick::moveIndicator(const Vec2 &origin, const Vec2 &pt)
{
	STATE_GUARD(getView(), TAG "moveIndicator", VOID);

	const float distance = abs((pt - origin).length());
	m_indicators[1]->setPosition(pt);
	m_indicators[1]->setOpacity(MathUtils::Clamp<Uint>(0,
			distance / 32.0f * 0xC0, 0xC0));

	m_indicator_line->setPosition(origin.lerp(pt, 0.5f));
	m_indicator_line->setScaleY(MathUtils::Clamp<float>(0.0f, distance / 192.0f,
			1.5f));
	// gl uses right-hand rule
	m_indicator_line->setRotation(-MathUtils::GetAngleFromX(origin, pt) + 90);
	m_indicator_line->setOpacity(MathUtils::Clamp<Uint>(0,
			distance / 128.0f * 0x90, 0x90));
}

void AreaJoystick::endIndicator()
{
	STATE_GUARD(getView(), TAG "endIndicator", VOID);
	m_indicators[0]->runAction(FadeTo::create(0.1f, 0));
	m_indicators[1]->runAction(FadeTo::create(0.1f, 0));
	m_indicator_line->runAction(FadeTo::create(0.1f, 0));
}

}
