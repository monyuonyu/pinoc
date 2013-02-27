/*
 * XMODEM.c
 *
 *  Created on: 2011/02/27
 *      Author: mizu
 */

#include "3069f_sci.h"
#include "XMODEM.h"
#include "stdio.h"


#define ACK 0x06
#define NAK 0x15
#define EOT 0x04

void (*xwrite)(char c);
char (*xread)(void);
char (*xread_pol)(void);

#define XMODEM_DBG 0

// �ʐM���J�n�����Ɗ֐��𔲂��܂�
static int xmodem_start_nak()
{
	unsigned long cnt = 0;

	// �����l������܂ň��Ԋu���Ƃ�NAK�𑗐M
	while (!(xread_pol()))
	{
		if (cnt++ > 400000)
		{
			xwrite(XMODEM_NAK);
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
	block_num_rec = xread();
	if(block_num_now != block_num_rec)
		return 1;

	// �r�b�g���]�̃u���b�N�ԍ��m�F
	c = block_num_rec;
	block_num_rec = xread();
	block_num_rec ^= c;
	if(block_num_rec != 0xFF)
		return 1;

	// 128byte�̃f�[�^��M
	for(i = 0; i < XMODEM_BLOCK_SIZE; i++)
	{
		c = xread();
		*(buff++) = c;
		check_sum += c;
	}

	// �`�F�b�N�T���m�F
	c = xread();
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
	int i;
//	int starting = 0;

	printf("-------- xmodem_start --------\n");

	xmodem_start_nak();

	while(1)
	{
		c = sci_read_byte(SCI_NO_1);

		if(c == XMODEM_SOH)
		{
			sci_read_byte(SCI_NO_1); //	�u���b�N
			sci_read_byte(SCI_NO_1); //	�u���b�N���]
			for(i = 0; i < 128; i++)
			{
				buf[i] = sci_read_byte(SCI_NO_1);
//				i++;
			}
			sci_read_byte(SCI_NO_1); // �`�F�b�N�T��
			sci_write(SCI_NO_1, XMODEM_ACK);
		}

		if(c == XMODEM_EOT)
		{
			sci_write(SCI_NO_1, XMODEM_ACK);
		}
	}








//	while(1)
//	{
//
////		printf("recv header\n");
//		c = xread(); // �w�b�_��M
//
//		switch(c)
//		{
//		case XMODEM_SOH:	// �ʐM�J�n�I

//			if(xmodem_read_block(block_num_now, buf))
//			{
//				xwrite(XMODEM_NAK);	// ���s��ʒm
//			}
//			else
//			{
//				block_num_now++;
//				buf += XMODEM_BLOCK_SIZE;		// �o�b�t�@�̃|�C���^��1�u���b�N�i�߂�
//				xwrite(XMODEM_ACK);	// ������ʒm �� ���̃u���b�N���M�J�n
//			}
//			break;
//
//		case XMODEM_EOT:	// �]������
////			printf("XMODEM_EOT\n");
//			xwrite(XMODEM_ACK);
//			return block_num_now;
//
//		case XMODEM_CAN:	// ���f
//			return 0;
//
//		case XMODEM_EOF:
//			return 0;
//
////		default:
//
//		}
//
//	}
}


void xmodem_init(void (*io_write)(char c), char (*io_read)(void), char (*io_read_pol)(void))
{
	xwrite = io_write;
	xread = io_read;
	xread_pol = io_read_pol;
}


