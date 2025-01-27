/***********************************************************************/
/*                                                                     */
/*  FILE        :dbsct.c                                               */
/*  DATE        :Thu, Feb 21, 2013                                     */
/*  DESCRIPTION :Setting of B,R Section                                */
/*  CPU TYPE    :H8/3069R                                              */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.16).    */
/*                                                                     */
/***********************************************************************/
                  


#include "typedefine.h"

#pragma section $DSEC
#if __STDC_VERSION__ == 199901L
extern const struct {
#else
static const struct{
#endif
	_UBYTE *rom_s;       /* Start address of the initialized data section in ROM */
	_UBYTE *rom_e;       /* End address of the initialized data section in ROM   */
	_UBYTE *ram_s;       /* Start address of the initialized data section in RAM */
#if __STDC_VERSION__ == 199901L
}_DTBL[]= {
#else
}DTBL[]= {
#endif
	{__sectop("D"), __secend("D"), __sectop("R")},
//	{__sectop("$ABS8D"), __secend("$ABS8D"), __sectop("$ABS8R")},
//	{__sectop("$ABS16D") , __secend("$ABS16D") , __sectop("$ABS16R") }
};
#pragma section $BSEC
#if __STDC_VERSION__ == 199901L
extern const struct {
#else
static const struct {
#endif
	_UBYTE *b_s;         /* Start address of non-initialized data section */
	_UBYTE *b_e;         /* End address of non-initialized data section */
#if __STDC_VERSION__ == 199901L
}_BTBL[]= {
#else
}BTBL[]= {
#endif
	{__sectop("B"), __secend("B")},
//	{__sectop("$ABS8B"), __secend("$ABS8B")},
//	{__sectop("$ABS16B"), __secend("$ABS16B")}
};
