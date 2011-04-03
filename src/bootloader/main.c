/*
 * main.c
 *
 *  Created on: 2010/11/27
 *      Author: pino
 */

#include "3069f_io.h"
#include "3069f_sci.h"
#include "XMODEM.h"
#include "load_mot.h"
#include "ctype.h"

#include "string.h"
#include "stdlib.h"
#include "dbg.hpp"
//#include "DP8390.h"

extern int buf_start;
extern int text_start;

void getstring(char* buf)
{

	int i;
	int cnt = 0;
	for (i = 0; i < 30; i++)
	{
		buf[cnt] = tolower(sci_read_byte(SCI1));
		sci_write(SCI1, buf[cnt]);

		if (buf[cnt] == 0x0d)
		{
			buf[cnt] = 0x00;
			break;
		}
		cnt++;
	}
}

int main()
{
//	long i;
//	static int ii;
//	const char str[][32] = {{"ok sci\n\r"}, {"ok bootloader\n\r"}, {"ok started!! XMODEM\n\r"}, {"ok finish!! XMODEM\n\r"}, {"ok started!! Deploy\n\r"}, {"ok finish!! Deploy\n\r"}};

	// �|�[�g4�����炷�e�X�g
//	volatile unsigned char* p4ddr = (volatile unsigned char*) 0xFEE003;
//	volatile unsigned char* p4 = (volatile unsigned char*) 0xFFFFD3;
//	*p4ddr = 0x03;
//	*p4 = 0x01;

//	sci_write_str(SCI1, str[0]);
//
//	sci_write_str(SCI1, str[2]);
//	ii = xmodem_start(buf_start);
//	sci_write_str(SCI1, str[3]);
//
//	sci_write_str(SCI1, str[4]);
//	mot_deploy(buf_start);
//	sci_write_str(SCI1, str[5]);

//	sci_write_str(SCI1, (const char*)buf_start);

//	sci_write_str(SCI1, str[1]);

//	*p4 = 0x02;

	dbg();

//	sci_write_str(SCI1, (char*)&text_start);

	void (*start)(void);
	char str[32] = {0,};
	while(1)
	{
		int i;
		sci_write_str(SCI1, "pinocld>_ ");

		// �G���^�[�����͂����܂Ń��[�v
		getstring(str);

		sci_write(SCI1, '\n');

		// ���C���X�C�b�`
		switch (str[0])
		{
		// RAM�փ��[�h
		case 'l':
			sci_write_str(SCI1, "ok started!! XMODEM\n\r");
			xmodem_start((char*)&buf_start);
			sci_write_str(SCI1, "ok finish!! XMODEM\n\r");
			break;
			// void main(void) �̌`���Ŋ֐��|�C���^����J�n
		case 's':
			start = (void*)&buf_start;
			start();
			break;
			// �������_���v
		case 'd':
			getstring(str);
			asciitobin(str, 4);

			for (i = 0; i < (int)*((short*)str); i++)
				sci_write(SCI1, *(((char*)&buf_start) + i));
			break;
			// �w���v
		case 'h':
			break;

		}

	}

	return 0;
}

void init()
{
	extern int bss_start, bss_end, data_start, data_end, rodata_end;

	memset(&bss_start, 0, (long)&bss_end - (long)&bss_start);					// Bss�Z�N�V����������
	memcpy(&data_start, &rodata_end, (long)&data_end - (long)&data_start);		// data�Z�N�V����������
	memset(&buf_start, 0, (long*)0x600);												// buf�Z�N�V����������

	sci_init(SCI1, br9600);

	main();
}
