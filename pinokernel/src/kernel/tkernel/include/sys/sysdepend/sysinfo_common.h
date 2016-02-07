/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 2.0 Software Package
 *
 *    Copyright (C) 2006-2014 by Ken Sakamura.
 *    This software is distributed under the T-License 2.0.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2014/09/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)sysinfo_common.h (sys)
 *
 *	System shared information
 */

#ifndef __SYS_SYSINFO_COMMON_H__
#define __SYS_SYSINFO_COMMON_H__

// #ifdef APP_AT91
// #  include <sys/sysdepend/app_at91/sysinfo_depend.h>
// #endif

// #ifdef APP_H8S2212
// #  include <sys/sysdepend/app_h8s2212/sysinfo_depend.h>
// #endif

// #ifdef _APP_MB9AF312K_
// #  include <sys/sysdepend/app_mb9af312k/sysinfo_depend.h>
// #endif

#ifdef _APP_RL78G13_R5F100ADASP_
#  include <sys/sysdepend/app_rl78g13_r5f100adasp/sysinfo_depend.h>
#endif

#endif /* __SYS_SYSINFO_COMMON_H__ */
