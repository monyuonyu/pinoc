/***********************************************************************/
/*                                                                     */
/*  FILE        :DRAM_test.c                                           */
/*  DATE        :Fri, Nov 11, 2011                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3069R                                              */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.16).    */
/*                                                                     */
/***********************************************************************/

#include "iodefine.h"
#include "3069f_sci.h"
#include "stdlib.h"

/**
 * 型番:HM5117800
 * H83069 port モード5拡張モード CS2割り当て
 * メモリ番地 : 0x400000 ~ 5FFFFF
 * D0 - p34/D12
 * D1 - p35/D13
 * D2 - p36/D14
 * D3 - p37/D15
 * D4 - p33/D11
 * D5 - p32/D10
 * D6 - p31/D9
 * D7 - p30/D8
 * A0 - p10/A0
 * A1 - p11/A1
 * A2 - p12/A2
 * A3 - p13/A3
 * A4 - p14/A4
 * A5 - p15/A5
 * A6 - p16/A6
 * A7 - p17/A7
 * A8 - p20/A8
 * A9 - p21/A9
 * A10/R - p22/A10
 * RAS - p82/cs2
 * WE - p64/rd
 * CAS - pb4/ucas
 *
 */
void exp_memory_init()
{
	int i;

//	P8DDR |= 0x04; //CS2信号 ※回路が反転している
	P1DDR |= 0xFF;	//address 0~7
	P2DDR |= 0x07;	//data 8~9
	//P30~7,p82,p64,pb4は自動的ににDRAMバスとして稼働

	BSC.RTCOR = 99;	 // リフレッシュタイムコンスタントレジスタ
	BSC.RTMCSR.BYTE = 0x0F;	// リフレッシュタイマ コンペアマッチ
	BSC.DRCRB.BYTE = 0x98;	// DRAMコントロールレジスタB カラムアドレス10bit
	BSC.DRCRA.BIT.DRAS = 0x01;	// DRAMコントロールレジスタA CS2選択
	//	BSC.DRCRA.BYTE = 0x3C;	// DRAMコントロールレジスタA

	for(i = 0; i < 1000; i++);
}

void memory_main(void)
{
	unsigned long int i;
	char str[18] ={0,};

	exp_memory_init();
	sci_init(SCI_NO_1, BitRate_type_br9600);
	sci_write_str(SCI_NO_1, "This is DRAM test!!\r\n");

	// 外部RAM確認
	*(short*)0x410000 = 0x5678;
	sci_write(SCI_NO_1, *(char*)(0x410000 + 0));
	sci_write(SCI_NO_1, *(char*)(0x410000 + 1));

	for(i = 0; i < 0x1FFFFF; i++)
	{
		*(char*)(0x400000 + i) = i % 0xFF;
	}

	for(i = 0; i < 0x1FFFFF; i++)
	{
		sci_write(SCI_NO_1, *(char*)(0x400000 + i));
	}

	while(1);
}

