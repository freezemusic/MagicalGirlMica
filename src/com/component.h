/*
 * component.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include "misc_type.h"

namespace mica
{
namespace com
{

class Component
{
public:
	virtual ~Component()
	{}

	/**
	 * Return the unique component id for @a that
	 *
	 * @param that
	 * @return
	 * @see registerComponent()
	 */
	static Uint getComponentId(const Component *that)
	{
		return that->getComponentId_();
	}

protected:
	/**
	 * Register a component. This method should be called once in every derived
	 * class to pick up their unique component id. Generally this is to be done
	 * in getComponentId():
	 * @code
	 * static Uint getComponentId()
	 * {
	 *     static Uint id = registerComponent();
	 *     return id;
	 * }
	 * @endcode
	 *
	 * @note Beware, not thread-safe
	 * @return
	 */
	static Uint registerComponent()
	{
		static Uint id = 0;
		return id++;
	}

private:
	virtual Uint getComponentId_() const = 0;
};

}
}
