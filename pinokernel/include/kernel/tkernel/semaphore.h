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
 *	semaphore.h
 *	Semaphore
 */

#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

/*
 * Semaphore control block
 */
typedef struct semaphore_control_block {
	QUEUE	wait_queue;	/* Semaphore wait queue */
	ID	semid;		/* Semaphore ID */
	void	*exinf;		/* Extended information */
	ATR	sematr;		/* Semaphore attribute */
	INT	semcnt;		/* Semaphore current count value */
	INT	maxsem;		/* Semaphore maximum count value */
#if USE_OBJECT_NAME
	UB	name[OBJECT_NAME_LENGTH];	/* name */
#endif
} SEMCB;

IMPORT SEMCB knl_semcb_table[];	/* Semaphore control block */
IMPORT QUEUE knl_free_semcb;	/* FreeQue */

#define get_semcb(id)	( &knl_semcb_table[INDEX_SEM(id)] )


#endif /* _SEMAPHORE_H_ */
