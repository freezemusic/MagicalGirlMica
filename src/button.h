/*
 * button.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <libutils/type/coord.h>

#include "listenable.h"

namespace mica
{

class Button : public Listenable<Button>
{
public:
	virtual ~Button()
	{}

	operator bool() const
	{
		return m_is_good;
	}

	virtual bool isDown() const = 0;

protected:
	void setGood(const bool flag)
	{
		m_is_good = flag;
	}

private:
	bool m_is_good = true;
};

}
