/*
 * stage_object.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

namespace cocos2d
{

class Node;

}

namespace mica
{

class StageObject
{
public:
	virtual ~StageObject()
	{}

	operator bool() const
	{
		return m_is_good;
	}

	virtual cocos2d::Node* getView() = 0;

	virtual void interact(StageObject*) = 0;

protected:
	void setGood(const bool flag)
	{
		m_is_good = flag;
	}

private:
	bool m_is_good = false;
};

}
