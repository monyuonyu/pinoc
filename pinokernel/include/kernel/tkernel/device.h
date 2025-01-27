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
 *	device.h
 *	Device Management Function
 */

#ifndef _DEVICE_H_
#define _DEVICE_H_

/* Set Object Name in .exinf for DEBUG */
#define OBJNAME_DMMBF	"DEvt"		/* Event notification mbf */
#define OBJNAME_DMSEM	"DMSy"		/* semaphore of synchronous control */
#define OBJNAME_DMLOCK	"DMLk"		/* Multi-lock for Dev.Mgr. */

IMPORT	T_IDEV		knl_DefaultIDev;

#include "task.h"
/*
 *	Device registration management
 */

IMPORT DevCB knl_DevCBtbl[];	/* Device registration information table */
IMPORT QUEUE knl_UsedDevCB;	/* In-use queue */
IMPORT QUEUE knl_FreeDevCB;	/* Unused queue */

#define MAX_UNIT	255		/* Maximum number of subunits */

/*
 * Verify validity of device ID
 */
ER knl_check_devid( ID devid )
{
	devid >>= 8;
	if ( devid < 1 || devid > CFN_MAX_REGDEV ) {
		return E_ID;
	}
	return E_OK;
}

/*
 * Device Management: Input/Output
 */
IMPORT OpnCB knl_OpnCBtbl[];	/* Open management information table */
IMPORT QUEUE knl_FreeOpnCB;	/* Unused queue */

#define DD(opncb)		( (opncb) - knl_OpnCBtbl + 1 )
#define OPNCB(dd)		( knl_OpnCBtbl + ((dd) - 1) )

IMPORT ReqCB knl_ReqCBtbl[];	/* Request management information table */
IMPORT QUEUE knl_FreeReqCB;	/* Unused queue */

#define REQID(reqcb)		( (reqcb) - knl_ReqCBtbl + 1 )
#define REQCB(reqid)		( knl_ReqCBtbl + ((reqid) - 1) )

#define DEVREQ_REQCB(devreq)	((ReqCB*)((B*)(devreq) - offsetof(ReqCB, req)))

IMPORT ResCB knl_resource_control_block;


#include "limits.h"

/* Suspend disable request count */
IMPORT	INT	knl_DisSusCnt;

/* Maximum number of suspend disable request counts */
#define MAX_DISSUS	INT_MAX


/*
 * Device driver abort function call
 */
ER knl_call_abortfn( DevCB *devcb, ID tskid, T_DEVREQ *devreq, INT nreq )
{
	ER ercd;
	ABTFN	abortfn;

	abortfn = (ABTFN)devcb->ddev.abortfn;

	DISABLE_INTERRUPT;
	knl_ctxtsk->sysmode++;
	ENABLE_INTERRUPT;
#if TA_GP
	ercd = knl_CallDeviceDriver(tskid, devreq, nreq, devcb->ddev.exinf,
						(FP)abortfn, devcb->ddev.gp);
#else
	ercd = (*abortfn)(tskid, devreq, nreq, devcb->ddev.exinf);
#endif
	DISABLE_INTERRUPT;
	knl_ctxtsk->sysmode--;
	ENABLE_INTERRUPT;

	return ercd;
}


IMPORT ID knl_request( ID dd, W start, void *buf, W size, TMO tmout, INT cmd );
IMPORT BOOL knl_chkopen( DevCB *devcb, INT unitno );
IMPORT void knl_delReqCB( ReqCB *reqcb );
IMPORT ResCB* knl_GetResCB( void );
IMPORT void knl_delOpnCB( OpnCB *opncb, BOOL free );
IMPORT ER knl_close_device( OpnCB *opncb, UINT option );

#endif /* _DEVICE_H_ */
