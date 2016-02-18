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
 *	@(#)sysdef_common.h (tk)
 *
 *	System dependencies definition.
 *	Included also from assembler program.
 */

#ifndef __TK_SYSDEF_COMMON_H__
#define __TK_SYSDEF_COMMON_H__

// #if APP_AT91
// #  include <tk/sysdepend/app_at91/sysdef_depend.h>
// #endif

// #if APP_H8S2212
// #  include <tk/sysdepend/app_h8s2212/sysdef_depend.h>
// #endif

// #if APP_MB9AF312K
// #  include <tk/sysdepend/app_mb9af312k/sysdef_depend.h>
// #endif

#if _APP_RL78G13_R5F100ADASP_
#  include <tk/sysdepend/app_rl78g13_r5f100adasp/sysdef_depend.h>
#endif

#endif /* __TK_SYSDEF_COMMON_H__ */
