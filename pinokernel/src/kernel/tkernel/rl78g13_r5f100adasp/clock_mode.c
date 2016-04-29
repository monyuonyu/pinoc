/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 2.0 Software Package
 *
 *    Copyright (C) 2006-2014 by Ken Sakamura.
 *    This software is distributed under the T-License 2.0.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2014/09/01.
 *    distribute by pkernel github(https://github.com/monyuonyu/) at 2016/04/29.
 *
 *----------------------------------------------------------------------
 */
/*--------------------------------------------------------------------*/
/*  Include definition                                                */
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*  Struct definition                                                 */
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*  Constant definition                                               */
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*  Variable definition                                               */
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*  Macro definition                                                  */
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*  Prototype declaration                                             */
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*  Function definition                                               */
/*--------------------------------------------------------------------*/

#include <typedef.h>

EXPORT void init_clock_control(void)
{
#if (HWWD_DISABLE)				/* HW Watchdog Disable */

#endif

#if (CLOCK_SETUP)				/* Clock Setup */

#endif

#if (CR_TRIM_SETUP)

#endif
}
