/*
 * log.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <libutils/log.h>

#if defined(DEBUG) && !defined(NO_LOG)
	#undef NO_LOG

	#define LOG LU_LOG
	#define LOG_WTF(tag, msg) LU_LOG_WTF(tag, msg)
	#define LOG_E(tag, msg) LU_LOG_E(tag, msg)
	#define LOG_W(tag, msg) LU_LOG_W(tag, msg)
	#define LOG_I(tag, msg) LU_LOG_I(tag, msg)
	#define LOG_D(tag, msg) LU_LOG_D(tag, msg)
	#define LOG_V(tag, msg) LU_LOG_V(tag, msg)
#else
	#undef LOG
	#ifndef NO_LOG
		#define NO_LOG
	#endif

	#define LOG_WTF(tag, msg)
	#define LOG_E(tag, msg)
	#define LOG_W(tag, msg)
	#define LOG_I(tag, msg)
	#define LOG_D(tag, msg)
	#define LOG_V(tag, msg)
#endif

