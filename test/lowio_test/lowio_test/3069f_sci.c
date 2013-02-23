/*
 * sci.c
 *
 *  Created on: 2010/11/27
 *      Author: pino
 */

#include "3069f_sci.h"

static struct{
	volatile struct SCI *sci;
}regs[3] =
{
	{SCI0A},
	{SCI1A},
	{SCI2A},
};

void sci_init(SCI_NO no, BitRate_type_t type)
{
	int i;

	volatile struct SCI* sci = regs[no].sci;

	sci->SCR.BYTE = 0;
	sci->SMR.BYTE = 0;
	sci->BRR = type;

	// wait
	for(i = 0; i < 1;i++);

	// ����M����
	sci->SCR.BIT.RE = 1;
	sci->SCR.BIT.TE = 1;

	sci->SSR.BYTE = 0;
}

/********************************************************************************
	�|�[�����O
********************************************************************************/
void sci_write(SCI_NO no, char c)
{
	volatile struct SCI* sci = regs[no].sci;

	while(!sci->SSR.BIT.TDRE);
	sci->TDR = c;
	sci->SSR.BIT.TDRE = 0;

//	while(sci->SSR.BIT.TEND);

}

void sci_write_str(SCI_NO no,const char* _Str)
{
	volatile struct SCI* sci = regs[no].sci;

	while(*_Str)
	{
		sci_write(no, *_Str++);
	}

	// �o�b�t�@�̒��g���S�đ��M�����܂őҋ@
	while(!sci->SSR.BIT.TEND);
}

// �f�[�^��1byte������M����
char sci_read_byte(SCI_NO no)
{
	volatile struct SCI* sci = regs[no].sci;
	char c;

	// �f�[�^���i�[�����܂őҋ@
	while (1)
	{
		if (sci->SSR.BIT.ORER)
		{
			sci_write_str(no, "Error_sci over run");
			sci->SSR.BIT.ORER = 0;
		}
		if (sci->SSR.BIT.PER)
		{
			sci_write_str(no, "Error_sci parity");
			sci->SSR.BIT.PER = 0;
		}
		if (sci->SSR.BIT.FER_ERS)
		{
			sci_write_str(no, "Error_sci flaming");
			sci->SSR.BIT.FER_ERS = 0;
		}

		// �f�[�^���i�[����Ă��邩�m�F
		if (sci->SSR.BIT.RDRF)
			break;
	}

	c = sci->RDR;
	sci->SSR.BIT.RDRF = 0;

	return c;
}

// �A�������f�[�^����M
void sci_read(SCI_NO no, char* buff, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		*(buff++) = sci_read_byte(no);
	}
}

// �f�[�^����M���Ă��邩�m�F����B
// �|�[�����O�Ŋm�F����
// �i�[����Ă����1��Ԃ��A�i�[����Ă��Ȃ���΁A0��Ԃ�
int sci_read_pol(SCI_NO no)
{
	volatile struct SCI* sci = regs[no].sci;

	if (sci->SSR.BIT.ORER)
	{
		sci_write_str(no, "Error_sci over run");
		sci->SSR.BIT.ORER = 0;
	}
	if (sci->SSR.BIT.PER)
	{
		sci_write_str(no, "Error_sci parity");
		sci->SSR.BIT.PER = 0;
	}
	if (sci->SSR.BIT.FER_ERS)
	{
		sci_write_str(no, "Error_sci flaming");
		sci->SSR.BIT.FER_ERS = 0;
	}

	// �f�[�^���i�[����Ă��邩�m�F
	if (sci->SSR.BIT.RDRF)
		return 1;

	return 0;
}

void charput(char c)
{
	sci_write(SCI_NO_1, c);
}

char charget()
{
	char c;
	c = sci_read_byte(SCI_NO_1);

	return c;
}

/********************************************************************************
	���荞��
********************************************************************************/
char sci_read_byte_intr(SCI_NO no)
{
	volatile struct SCI* sci = regs[no].sci;
	char c;

	c = sci->RDR;
	sci->SSR.BIT.RDRF = 0;

	return c;
}
// ���M�������荞��Enable
void sci_write_intr_enable(SCI_NO no)
{
	volatile struct SCI* sci = regs[no].sci;
	sci->SCR.BIT.TIE = 1;
}

// ���M�������荞��Disable
void sci_write_intr_disable(SCI_NO no)
{
	volatile struct SCI* sci = regs[no].sci;
	sci->SCR.BIT.TIE = 0;
}

// ��M�������荞��Enable
void sci_read_intr_enable(SCI_NO no)
{
	volatile struct SCI* sci = regs[no].sci;
	sci->SCR.BIT.RIE = 1;
}

// ��M�������荞��Disable
void sci_read_intr_disable(SCI_NO no)
{
	volatile struct SCI* sci = regs[no].sci;
	sci->SCR.BIT.RIE = 1;
}



