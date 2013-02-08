/*
 * XMODEM.c
 *
 *  Created on: 2011/02/27
 *      Author: mizu
 */

#include "3069f_sci.h"
#include "XMODEM.h"

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

#define ACK 0x06
#define NAK 0x15
#define EOT 0x04

void (*write)(char c);
char (*read)(void);
char (*read_pol)(void);

#define XMODEM_DBG 0

// �ʐM���J�n�����Ɗ֐��𔲂��܂�
static int xmodem_start_ack()
{
	unsigned long cnt = 0;

	// �����l������܂ň��Ԋu���Ƃ�NAK�𑗐M
	while (!(read_pol()))
	{
		if (cnt++ > 200000)
		{
			write(XMODEM_NAK);
			cnt = 0;

		}
	}
	return 0;
}


// XMODEM 1�u���b�N��M
static int xmodem_read_block(unsigned char block_num_now, char* buff)
{
	unsigned char c, block_num_rec, check_sum = 0;
//	char c;
	int i;

	// �u���b�N�ԍ��m�F
	block_num_rec = read();
	if(block_num_now != block_num_rec)
		return 1;

	// �r�b�g���]�̃u���b�N�ԍ��m�F
	c = block_num_rec;
	block_num_rec = read();
	block_num_rec ^= c;
	if(block_num_rec != 0xFF)
		return 1;

	// 128byte�̃f�[�^��M
	for(i = 0; i < XMODEM_BLOCK_SIZE; i++)
	{
		c = read();
		*(buff++) = c;
		check_sum += c;
	}

	// �`�F�b�N�T���m�F
	c = read();
	check_sum ^= c;
	if(check_sum)
		return 1;

	// ����I��
	return 0;

}

// �]������������Ɠ]�������u���b�N���B ���s�E���f�����0��Ԃ�
int xmodem_start(char* buf)
{
	unsigned char block_num_now = 1;
	char c;
	int starting = 0;

	while(1)
	{
		if(!starting)
		{
			xmodem_start_ack();
		}

		c = read(); // �w�b�_��M

		switch(c)
		{
		case XMODEM_SOH:	// �ʐM�J�n�I
			starting = 1;
			if(xmodem_read_block(block_num_now, buf))
			{
				write(XMODEM_NAK);	// ���s��ʒm
			}
			else
			{
				block_num_now++;
				buf += XMODEM_BLOCK_SIZE;		// �o�b�t�@�̃|�C���^��1�u���b�N�i�߂�
				write(XMODEM_ACK);	// ������ʒm �� ���̃u���b�N���M�J�n
			}
			break;

		case XMODEM_EOT:	// �]������
			write(XMODEM_ACK);
			return block_num_now;

		case XMODEM_CAN:	// ���f
			return 0;

		case XMODEM_EOF:
			return 0;

//		default:

		}

	}
}


void xmodem_init(void (*io_write)(char c), char (*io_read)(void), char (*io_read_pol)(void))
{
	write = io_write;
	read = io_read;
	read_pol = io_read_pol;
}

/**
 * ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
 * ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
 */


void test_write(char c)
{
	sci_write(SCI_NO_1, c);
}

char test_read()
{
	char c;
	c = sci_read_byte(SCI_NO_1);
	return c;
}

char test_read_pol()
{
	char c = 0x00;
	c = sci_read_pol(SCI_NO_1);
	return c;
}

void main(void)
{
	static char buff[512] = {0,};
	int i;

	sci_init(SCI_NO_1, BitRate_type_br9600);
	xmodem_init(test_write, test_read, test_read_pol);
	xmodem_start(buff);

	for(i = 0; i < 200; i++)
	{
		sci_write(SCI_NO_1, buff[i]);
	}

	while(1);
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
