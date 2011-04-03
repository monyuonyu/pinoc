/*
 * load_mot.h
 *
 *  Created on: 2011/03/28
 *      Author: mizu
 */

#ifndef LOAD_MOT_H_
#define LOAD_MOT_H_

/********************************************************************************
	�w�b�_�[���R�[�h
 ********************************************************************************/
struct mot_S0
{
	char record[2];		// ���R�[�h�`��
	char byte_count[2];	// �o�C�g�J�E���g
	char load_addr[4];	// ���[�h�A�h���X
};
/********************************************************************************
	�f�[�^���R�[�h
 ********************************************************************************/
struct mot_S1
{
	char record[2];		// ���R�[�h�`��
	char byte_count[2];	// �o�C�g�J�E���g
	char load_addr[4];	// ���[�h�A�h���X(2byte�A�h���X)
};

struct mot_S2
{
	char record[2];		// ���R�[�h�`��
	char byte_count[2];	// �o�C�g�J�E���g
	char load_addr[6];	// ���[�h�A�h���X(3byte�A�h���X)
};

struct mot_S3
{
	char record[2];		// ���R�[�h�`��
	char byte_count[2];	// �o�C�g�J�E���g
	char load_addr[8];	// ���[�h�A�h���X(4byte�A�h���X)
};

/********************************************************************************
	�G���h���R�[�h
 ********************************************************************************/
struct mot_S7
{
	char record[2];
	char byte_count[2];
	char load_addr[4];
};

struct mot_S8
{
	char record[2];
	char byte_count[2];
	char load_addr[6];
};

struct mot_S9
{
	char record[2];
	char byte_count[2];
	char load_addr[8];
};


/********************************************************************************
	�v���g�^�C�v�錾
********************************************************************************/
void mot_deploy(char* buf);

#endif /* LOAD_MOT_H_ */
