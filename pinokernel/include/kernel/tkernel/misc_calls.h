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
 *	misc_calls.h
 *	Other System Calls
 */

#ifndef _MISC_CALLS_H_
#define _MISC_CALLS_H_

IMPORT UINT	knl_lowpow_discnt;

/*
 * Hook routine address
 */
IMPORT FP knl_hook_enterfn;
IMPORT FP knl_hook_leavefn;
IMPORT FP knl_hook_execfn;
IMPORT FP knl_hook_stopfn;
IMPORT FP knl_hook_ienterfn;
IMPORT FP knl_hook_ileavefn;

#if TA_GP
IMPORT void *knl_hook_svc_gp;
IMPORT void *knl_hook_dsp_gp;
IMPORT void *knl_hook_int_gp;
#endif

/*
 * Hook enable/disable setting
 */
IMPORT void knl_hook_svc( void );
IMPORT void knl_unhook_svc( void );
IMPORT void knl_hook_dsp( void );
IMPORT void knl_unhook_dsp( void );
IMPORT void knl_hook_int( void );
IMPORT void knl_unhook_int( void );


#endif /* _MISC_CALLS_H_ */
