/**
 *******************************************************************************
 * @file ewol/Debug.h
 * @brief Ewol : log wrapper (header)
 * @author Edouard DUPIN
 * @date 19/10/2010
 * @par Project
 * Ewol
 *
 * @par Copyright
 * Copyright 2011 Edouard DUPIN, all right reserved
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY.
 *
 * Licence summary : 
 *    You can modify and redistribute the sources code and binaries.
 *    You can send me the bug-fix
 *
 * Term of the licence in in the file licence.txt.
 *
 *******************************************************************************
 */

#ifndef __EWOL_DRAWER_DEBUG_H__
#define __EWOL_DRAWER_EBUG_H__

#include <etk/Types.h>
#include <etk/Debug.h>

extern const char * ewolDrawer;

#define DRAW_CRITICAL(data)         ETK_CRITICAL(ewolDrawer, data)
// General 
#if DRAW_DEBUG_LEVEL > 0
#	define DRAW_WARNING(data)       ETK_WARNING(ewolDrawer, data)
#	define DRAW_ERROR(data)         ETK_ERROR(ewolDrawer, data)
#else
#	define DRAW_WARNING(data)       do {}while(0)
#	define DRAW_ERROR(data)         do {}while(0)
#endif

#if DRAW_DEBUG_LEVEL > 1
#	define DRAW_INFO(data)          ETK_INFO(ewolDrawer, data)
#else
#	define DRAW_INFO(data)          do {}while(0)
#endif

#if DRAW_DEBUG_LEVEL > 2
#	define DRAW_DEBUG(data)         ETK_DEBUG(ewolDrawer, data)
#else
#	define DRAW_DEBUG(data)         do {}while(0)
#endif

#if DRAW_DEBUG_LEVEL > 3
#	define DRAW_VERBOSE(data)         ETK_VERBOSE(ewolDrawer, data)
#else
#	define DRAW_VERBOSE(data)         do {}while(0)
#endif

#define DRAW_TODO(data)             DRAW_WARNING("TODO : " << data)

#define DRAW_ASSERT(cond, data)     ETK_ASSERT(ewolDrawer, cond, data)

#if DRAW_DEBUG_LEVEL > 1
#	define DRAW_CHECK_INOUT(cond)   ETK_CHECK_INOUT_ASSERT(ewolDrawer, cond)
#elif DRAW_DEBUG_LEVEL > 0
#	define DRAW_CHECK_INOUT(cond)   ETK_CHECK_INOUT_WARNING(ewolDrawer, cond)
#else
#	define DRAW_CHECK_INOUT(cond)   do { } while (0)
#endif

#endif

