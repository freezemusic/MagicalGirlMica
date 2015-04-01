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
	 * Return the unique component id
	 *
	 * @return
	 * @see registerComponent()
	 */
	virtual Uint getComponentId() const = 0;

protected:
	/**
	 * Register a component. This method should be called once in every derived
	 * class to pick up their unique component id. Generally this is to be done
	 * in a static method to get its unique component id:
	 * @code
	 * static Uint componentId()
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
};

}
}
