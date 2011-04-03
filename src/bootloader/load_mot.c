/*
 * load_mot.c
 *
 *  Created on: 2011/03/28
 *      Author: mizu
 */

#include "load_mot.h"
#include "XMODEM.h"
#include "3069f_sci.h"
#include "stdlib.h"
#include "string.h"

#define XMODEM_DBG 0


void mot_deploy(char* buf)
{
	static int mot_dst = 0;
	static int data_cnt = 0;
	char* addr_dst;
	unsigned char checksum = 0;
	int i;


	while (1)
	{

		// ����R�[�h�Ȃ�|�C���^��i�߂�
		while (buf[mot_dst] == 0x0A || buf[mot_dst] == 0x0D)
			mot_dst++;

		// ���g���[��S�R�[�h�łȂ���΃��^�[��
		if (buf[mot_dst] != 'S')
			return;

		// �o�C�g�J�E���^�ǂݍ���
		asciitobin(&buf[mot_dst + 2], 2);
		data_cnt = buf[mot_dst + 2] * 2;

		switch (buf[mot_dst + 1])
		{
		case '0': // �w�b�_�[�`��

			break;
		case '1':
			asciitobin(&buf[mot_dst + 4], data_cnt);
			addr_dst = (char*) *(&((short*) buf)[mot_dst + 2]);			// �� �G���f�B�A���ɒ���!!

			// Deploy
			for (i = 0; i < (data_cnt / 2) - 2 - 1; i++)
			{
				*addr_dst = buf[i + 6 + mot_dst];
				checksum += buf[i + 6 + mot_dst];
				addr_dst++;
			}

			// �`�F�b�N�T������
			checksum += buf[mot_dst + 2];
			checksum += buf[mot_dst + 4];
			checksum += buf[mot_dst + 5];
			checksum ^= buf[(data_cnt / 2) - 2 - 1 + mot_dst + 6];
			if (checksum != 0xFF)
			{
				return; // ���s
			}

			mot_dst += data_cnt + 4;

			break;
		case '2':
			break;
		case '3':
			break;
		case '8':	// �t�b�^
			break;
		case '9':
			return;

		default: // �Ή����Ă��Ȃ���΃��^�[��
			return;

		};

	}
}


// �]������������Ɠ]�������u���b�N���B ���s�E���f����ƂP��Ԃ�
int load_lod(char* buf)
{
	unsigned char block_num_now = 1;
	char c;
	int starting = 0;
//	int mot_no = 0;

	while (1)
	{
		if (!starting)
		{
			xmodem_start_ack();
		}

		sci_read(SCI1, &c, 1);

		switch (c)
		{
		case XMODEM_SOH: // �ʐM�J�n�I
			starting = 1;
			if (xmodem_read_block(block_num_now, buf))
			{
				sci_write(SCI1, XMODEM_NAK); // ���s��ʒm
			}
			else
			{
				/********************************************************************************
					���g���[��S�t�H�[�}�b�g���
				********************************************************************************/
				mot_deploy(buf);

//				if(buf[mot_no] == 'S' && buf[mot_no + 1] == '0')	// ��͊J�n
//				{
//
//				}

				block_num_now++;
//				buf += XMODEM_BLOCK_SIZE; // �o�b�t�@�̃|�C���^��1�u���b�N�i�߂�
				sci_write(SCI1, XMODEM_ACK); // ������ʒm �� ���̃u���b�N���M�J�n
			}
			break;

		case XMODEM_EOT: // �]������
			sci_write(SCI1, XMODEM_ACK);
			return block_num_now;

		case XMODEM_CAN: // ���f
			return 0;

		case XMODEM_EOF:
			return 0;

		default:
			if (starting)
				return 0;
		}

	}
}
