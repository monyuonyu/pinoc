/*
 * sci.h
 *
 *  Created on: 2010/11/27
 *      Author: pino
 */

#ifndef _SCI_H_
#define _SCI_H_

typedef unsigned char u1;
typedef unsigned int short u2;

#define BIT_CTL
#define C20MHZ 1
#define C25MHZ 0

#ifndef BIT_CTL
#define CKS0	(1 << 0)
#define CKS1	(1 << 1)
#define MP		(1 << 2)
#define STOP	(1 << 3)
#define OE		(1 << 4)
#define PE		(1 << 5)
#define CHR	(1 << 6)
#define CA		(1 << 7)
#define SHIFT_CTL

#else

#define CKS_1C	0x00
#define CKS_4C	0x01
#define CKS_16C	0x02
#define CKS_64C	0x03
#endif

#if C20MHZ
typedef enum {	//�����N���b�N20MHz
	BitRate_type_br4800  = 129,		// CKS=00
	BitRate_type_br9600  = 64,		// CKS=00
	BitRate_type_br19200 = 32,		// CKS=00
	BitRate_type_br38400 = 15		// CKS=00
}BitRate_type_t;
#endif

#if C25MHZ
typedef enum { 	//�����N���b�N25MHz
	BitRate_type_br4800  = 162,		// CKS=00
	BitRate_type_br9600  = 80,		// CKS=00
	BitRate_type_br19200 = 40,		// CKS=00
	BitRate_type_br38400 = 19		// CKS=00
}BitRate_type_t;
#endif

struct SCI
{
	union
	{
		u1 BYTE;
		struct
		{
			u1 CA		:1;		// 0=�������� 1=�N���b�N����
			u1 CHR		:1;		// 0=8bit data 1=7bit data
			u1 PE		:1;		// 0=�p���e�B�Ȃ� 1=�p���e�B����
			u1 OE		:1;		// 0=�����p���e�B 1=��p���e�B
			u1 STOP		:1;		// 0=�X�g�b�v�r�b�g��1bit 1=�X�g�b�v�r�b�g��2bit
			u1 MP		:1;		// 0=�V���O���v���Z�b�T 1=�}���`�v���Z�b�T
			u1 CKS1		:1;		// �N���b�N�Z���N�g
			u1 CKS0		:1;		// �N���b�N�Z���N�g
		}BIT;

		struct
		{
			u1 reserve	:6;
			u1 CKS		:2;
		}TEST;
	}SMR;

	u1 BRR;

	union
	{
		u1 BYTE;
		struct
		{
			u1 TIE		:1;		// ���M���������荞�� 0=TXI�֎~ 1=TXI����
			u1 RIE		:1;		// ��M���������荞�� 0=RXI�֎~ 1=RXI����
			u1 TE		:1;		// 0=���M�֎~ 1=���M����
			u1 RE		:1;		// 0=��M�֎~ 1=��M����
			u1 MPIE		:1;		// �}���`�v���Z�b�T���荞�� 0=�֎~ 1=����
			u1 TEIE		:1;		// ���M�I�����荞�� 0=�֎~ 1=����
			u1 CKE1		:1;		// 0=�����N���b�N(��������) 1=�O���N���b�N(�N���b�N������)
			u1 CKE0		:1;		// CKE1=0,0=SCI �́ASCK �[�q���g�p���܂��� CKE1=1,0=�r�b�g���[�g�Ɠ������g���̃N���b�N���o��
		}BIT;
	}SCR;

	u1 TDR;

	union
	{
		u1 BYTE;
		struct
		{
			u1 TDRE		:1;		// 0=TDR�ɗL���ȑ��M�f�[�^�����C�g����Ă��� 1=TDR�ɗL���ȑ��M�f�[�^���Ȃ�
								// �m�N���A�����nTDRE=1 �̏�Ԃ����[�h������A0 �����C�g�����Ƃ�, DMAC ��TDR �փf�[�^�����C�g�����Ƃ�
								// �m�Z�b�g�����nTDR ����TSR �Ƀf�[�^�]�����s����TDR �Ƀf�[�^���C�g���\�ɂȂ����Ƃ�, SCR ��TE �r�b�g��0 �̂Ƃ�, ���Z�b�g�A�܂��̓X�^���o�C���[�h��
			u1 RDRF		:1;		// 0=RDR�Ɏ�M�f�[�^���i�[����Ă��Ȃ� 1=RDR�Ɏ�M�f�[�^���i�[����Ă���
								// �m�N���A�����nDMAC��RDR �̃f�[�^�����[�h�����Ƃ�, RDRF=1 �̏�Ԃ����[�h������A0 �����C�g�����Ƃ�, ���Z�b�g�A�܂��̓X�^���o�C���[�h��
								// �m�Z�b�g�����n�V���A����M������I�����ARSR ����RDR �֎�M�f�[�^���]�����ꂽ�Ƃ�
			u1 ORER		:1;		// 0=��M���A�܂��͐���Ɏ�M���������� 1=��M���ɃI�[�o�����G���[����������
			u1 FER_ERS	:1;		// 0=��M���A�܂��͐���Ɏ�M���������� 1=��M���Ƀt���[�~���O�G���[����������
			u1 PER		:1;		// 0=��M���A�܂��͐���Ɏ�M���������� 1=��M���Ƀp���e�B�G���[����������
			u1 TEND		:1;		// 0=���M���ł��� 1=���M���I������
			u1 MPB		:1;		// �}���`�v���Z�b�T�֘A
			u1 MPBT		:1;		//	"
		}BIT;
	}SSR;

	u1 RDR;

	union
	{
		u1 BYTE;
		struct
		{
			u1			:4;
			u1 SDIR		:1;
			u1 SINV		:1;
			u1			:1;
			u1 SMIF		:1;
		}BIT;
	}SCMR;
};

//typedef int SCI_NO;
//#define SCI_NO_0 0
//#define SCI_NO_1 1
//#define SCI_NO_2 2

typedef enum {
	SCI_NO_0 = 0,
	SCI_NO_1,
	SCI_NO_2
}SCI_NO;

#define SCI0A ((volatile struct SCI*)0xFFFFB0)
#define SCI1A ((volatile struct SCI*)0xFFFFB8)
#define SCI2A ((volatile struct SCI*)0xFFFFC0)

#define SMR0	0xFFFFB0 // �V���A�����[�h���W�X�^�iSMR)
#define BRR0	0xFFFFB1 // �r�b�g���[�g���W�X�^�iBRR�j
#define SCR0	0xFFFFB2 // �V���A���R���g���[�����W�X�^�iSCR�j
#define TDR0	0xFFFFB3 // �g�����X�~�b�g�f�[�^���W�X�^�iTDR)		���M�f�[�^
#define SSR0	0xFFFFB4 // �V���A���X�e�[�^�X���W�X�^�iSSR�j
#define RDR0	0xFFFFB5 // ���V�[�u�V�t�g���W�X�^�iRSR�j			��M�f�[�^
#define SCMR0	0xFFFFB6 // �X�}�[�g�J�[�h���[�h���W�X�^(SCMR)

#define SMR1	0xFFFFB8
#define BRR1	0xFFFFB9
#define SCR1	0xFFFFBa
#define TDR1	0xFFFFBb
#define SSR1	0xFFFFBc
#define RDR1	0xFFFFBd
#define SCMR1	0xFFFFBe

#define SMR2	0xFFFFC0
#define BRR2	0xFFFFC1
#define SCR2	0xFFFFC2
#define TDR2	0xFFFFC3
#define SSR2	0xFFFFC4
#define RDR2	0xFFFFC5
#define SCMR2	0xFFFFC6

#ifdef __cplusplus
extern "C"{
#endif

/********************************************************************************
	stdio���C�u��������̎Q��
********************************************************************************/
void charput(char c);
char charget();

/********************************************************************************
	�|�[�����O
********************************************************************************/
void sci_init(SCI_NO no, BitRate_type_t type);
void sci_write(SCI_NO no, char c);
void sci_write_str(SCI_NO no,const char* _Str);
void sci_read(SCI_NO no, char* buff, int size);
char sci_read_byte(SCI_NO no);
int sci_read_pol(SCI_NO no);

/********************************************************************************
	���荞��
********************************************************************************/
char sci_read_byte_intr(SCI_NO no);
void sci_write_intr_enable(SCI_NO no);
void sci_write_intr_disable(SCI_NO no);
void sci_read_intr_enable(SCI_NO no);
void sci_read_intr_disable(SCI_NO no);

#ifdef __cplusplus
}
#endif

#endif /* SCI_H_ */
