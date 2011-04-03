/*
 * DP8390.c
 *
 *  Created on: 2010/12/13
 *      Author: mizu
 */

#include "DP8390.h"

struct DP8390 nic;

void nic_mac_set()
{

}

// ON = 1 , OFF = 0
void nic_send_ON_OFF(int ON_OFF)
{
	if(ON_OFF)
		nic->TCR.LB0 = 0;
	else
		nic->TCR.LB0 = 1;
}

void nic_rec_ON_OFF(int ON_OFF)
{
	if(ON_OFF)
		nic->RCR.MON = 0;
	else
		nic->RCR.MON = 1;
}

void select_page(int page_no)
{
	nic->CR.PS = 0;

	switch(page_no)
	{
	case 0:					// page0
		break;
	case 1:
		nic->CR.PS0 = 1;	// page1
		break;
	case 2:
		nic->CR.PS1 = 1;	// page2
		break;

	}
}

void nic_init(void* nic_base)
{

	long i;


	nic = (struct DP8390*)nic_base;	// �x�[�X�A�h���X�Z�b�g

	u1 buff[16];

	(nic + 0x18) = 0x00;			// ���Z�b�g
	for(i = 0; i < 400000; i++);	// �E�F�C�g

	select_page(0);					// page0�I��

	nic->CR.STP = 1;				// �X�g�b�v
	nic->IMR = 0;					// ���荞�݃}�X�N�N���A
	nic->ISR = 0xFF;				// ���荞�ݗv���N���A
	nic->RBCR0 = 0;					// �����[�g�o�C�g�J�E���g���W�X�^0 �N���A
	nic->RBCR1 = 0;					// �����[�g�o�C�g�J�E���g���W�X�^1 �N���A
	nic->DCR.WTS = 1;				// ���[�h�]���w��
	nic->DCR.LS = 1;				// ���[�v�o�b�N�ݒ�
//	nic->DCR.FT1 = 1;

	nic_send_ON_OFF(0);				// ���M��OFF
	nic_rec_ON_OFF(0);				// ��M��OFF


	nic->PSTART = (0x4c00 >> 8);	// �����O�o�b�t�@�J�n�ʒu
	nic->PSTOP = (0x8000 >> 8);		// �����O�o�b�t�@�I���ʒu

	nic->BNRY = ((0x8000 >> 8) - 1);
	select_page(1);


}
