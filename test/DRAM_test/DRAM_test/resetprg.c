/***********************************************************************/
/*                                                                     */
/*  FILE        :resetprg.c                                            */
/*  DATE        :Fri, Nov 11, 2011                                     */
/*  DESCRIPTION :Reset Program                                         */
/*  CPU TYPE    :H8/3069R                                              */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.16).    */
/*                                                                     */
/***********************************************************************/
                  


#include	<machine.h>
#include	<_h_c_lib.h>
//#include	<stddef.h>					// Remove the comment when you use errno
//#include 	<stdlib.h>					// Remove the comment when you use rand()
#include	"typedefine.h"
#include	"stacksct.h"

extern void main(void);
__entry(vect=0) void PowerON_Reset(void);
//__interrupt(vect=1) void Manual_Reset(void);

//#ifdef __cplusplus				// Enable I/O in the application(both SIM I/O and hardware I/O)
//extern "C" {
//#endif
//extern void _INIT_IOLIB(void);
//extern void _CLOSEALL(void);
//#ifdef __cplusplus
//}
//#endif

//extern void srand(_UINT);		// Remove the comment when you use rand()
//extern _SBYTE *_s1ptr;				// Remove the comment when you use strtok()
		
//#ifdef __cplusplus				// Remove the comment when you use Hardware Setup
//extern "C" {
//#endif
//extern void HardwareSetup(void);
//#ifdef __cplusplus
//}
//#endif

//#ifdef __cplusplus			// Remove the comment when you use global class object
//extern "C" {					// Sections C$INIT and C$END will be generated
//#endif
//extern void _CALL_INIT(void);
//extern void _CALL_END(void);
//#ifdef __cplusplus
//}
//#endif
	
#pragma section ResetPRG

__entry(vect=0) void PowerON_Reset(void)
{ 
	 set_imask_ccr((_UBYTE)1);
	_INITSCT();

//	_CALL_INIT();					// Remove the comment when you use global class object

//	_INIT_IOLIB();					// Enable I/O in the application(both SIM I/O and hardware I/O)

//	errno=0;						// Remove the comment when you use errno
//	srand((_UINT)1);					// Remove the comment when you use rand()
//	_s1ptr=NULL;					// Remove the comment when you use strtok()
		
//	HardwareSetup();				// Remove the comment when you use Hardware Setup
	set_imask_ccr((_UBYTE)0);

	main();

//	_CLOSEALL();					// Close I/O in the application(both SIM I/O andhardware I/O)

//	_CALL_END();					// Remove the comment when you use global class object
	
	sleep();
}

//__interrupt(vect=1) void Manual_Reset(void)	// Remove the comment when you use Manual Reset
//{
//} 
