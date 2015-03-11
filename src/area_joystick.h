/*
 * area_joystick.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <libutils/type/coord.h>
#include <libutils/type/rect.h>

#include "on_screen_joystick.h"

namespace cocos2d
{

class Node;
class Touch;
class Vec2;

}

namespace mica
{

/**
 * A joystick that covers an invisible rectangular area. The center point would
 * be the point you dropped your finger
 */
class AreaJoystick : public OnScreenJoystick
{
public:
	struct Config
	{
		utils::type::Rect rect;
		bool is_visible = false;
	};

	explicit AreaJoystick(const Config &config);
	virtual ~AreaJoystick();

	utils::type::Coord getPosition() const override
	{
		return m_position;
	}

protected:
	AreaJoystick();

	bool init(const Config &config);
	void uninit();

	const utils::type::Rect& getRect() const
	{
		return m_rect;
	}

private:
	bool initView(const Config &config);
	bool initIndicator();
	bool initListeners();

	void updatePosition(const cocos2d::Touch &touch);

	void beginIndicator(const cocos2d::Vec2 &pt);
	void moveIndicator(const cocos2d::Vec2 &pt);
	void endIndicator();

	utils::type::Rect m_rect;
	utils::type::Coord m_position;

	cocos2d::Node* m_indicators[2];
	bool m_is_indicator_moved;
};

}
