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
 *	mutex.h
 *	Mutex
 */

#ifndef _MUTEX_H_
#define _MUTEX_H_

#ifndef __mtxcb__
#define __mtxcb__
typedef struct mutex_control_block	MTXCB;
#endif

/*
 * Mutex control block
 */
struct mutex_control_block {
	QUEUE	wait_queue;	/* Mutex wait queue */
	ID	mtxid;		/* Mutex ID */
	void	*exinf;		/* Extended information */
	ATR	mtxatr;		/* Mutex attribute */
	UB	ceilpri;	/* Highest priority limit of mutex */
	TCB	*mtxtsk;	/* Mutex get task */
	MTXCB	*mtxlist;	/* Mutex get list */
#if USE_OBJECT_NAME
	UB	name[OBJECT_NAME_LENGTH];	/* name */
#endif
};

IMPORT MTXCB knl_mtxcb_table[];	/* Mutex control block */
IMPORT QUEUE knl_free_mtxcb;	/* FreeQue */

#define get_mtxcb(id)	( &knl_mtxcb_table[INDEX_MTX(id)] )


/*
 * If there is a mutex 'mtxcb' with the task of lock wait, it is TRUE
 */
#define mtx_waited(mtxcb)	( !isQueEmpty(&(mtxcb)->wait_queue) )

/*
 * Return the highest priority in the task of lock wait at mutex 'mtxcb'
 */
#define mtx_head_pri(mtxcb)	( ((TCB*)(mtxcb)->wait_queue.next)->priority )

/*
 * Reset priority of lock get task (For TA_INHERIT only)
 */
#define reset_priority(tcb)	knl_release_mutex((tcb), NULL)


IMPORT void knl_release_mutex( TCB *tcb, MTXCB *relmtxcb );

#endif /* _MUTEX_H_ */
