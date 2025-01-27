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
 *	eventflag.h
 *	Event Flag
 */

#ifndef _EVENTFLAG_H_
#define _EVENTFLAG_H_

/*
 * Event flag control block
 */
typedef struct eventflag_control_block {
	QUEUE	wait_queue;	/* Event flag wait queue */
	ID	flgid;		/* Event flag ID */
	void	*exinf;		/* Extended information */
	ATR	flgatr;		/* Event flag attribute */
	UINT	flgptn;		/* Event flag current pattern */
#if USE_OBJECT_NAME
	UB	name[OBJECT_NAME_LENGTH];	/* name */
#endif
} FLGCB;

IMPORT FLGCB knl_flgcb_table[];	/* Event flag control block */
IMPORT QUEUE knl_free_flgcb;	/* FreeQue */

#define get_flgcb(id)	( &knl_flgcb_table[INDEX_FLG(id)] )


/*
 * Check for event flag wait release condition
 */
BOOL knl_eventflag_cond( FLGCB *flgcb, UINT waiptn, UINT wfmode )
{
	if ( (wfmode & TWF_ORW) != 0 ) {
		return ( (flgcb->flgptn & waiptn) != 0 );
	} else {
		return ( (flgcb->flgptn & waiptn) == waiptn );
	}
}


#endif /* _EVENTFLAG_H_ */
