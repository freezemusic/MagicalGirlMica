/*
 * property.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "misc_type.h"

namespace mica
{
namespace character
{

class Property
{
public:
	virtual ~Property()
	{}

	/**
	 * Return the unique property id
	 *
	 * @return
	 * @see registerProperty()
	 */
	virtual Uint getPropertyId() const = 0;

protected:
	/**
	 * Register a property. This method should be called once in every concrete
	 * class to pick up their unique property id. Generally this is to be done
	 * in getPropertyId():
	 * @code
	 * Uint getPropertyId() const override
	 * {
	 *     static Uint id = registerProperty();
	 *     return id;
	 * }
	 * @endcode
	 *
	 * @note Beware, not thread-safe
	 * @return
	 */
	static Uint registerProperty()
	{
		static Uint id = 0;
		return id++;
	}
};

}
}
