/*
 * misc_utils.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <libutils/str/str_utils.h>

#include "log.h"
#include "misc_type.h"

#define VOID
#define STATE_GUARD(expression, tag, ret) \
		if (!(expression)) { LOG_E(tag, utils::str::StrUtils::Concat("Illegal state @", __LINE__)); return ret; }
