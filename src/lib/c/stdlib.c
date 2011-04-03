/*
 * stdlib.c
 *
 *  Created on: 2011/03/28
 *      Author: mizu
 */

#include "stdlib.h"
#include "string.h"

int atoi(const char* _str)
{
	int cnt = 0;
	int val = 0;
	int magnifi = 1;

	// �u�����́v������̃P�^���J�E���g����
	while(1)
	{
		if(_str[cnt] == 0x00)	// NULL�ŃJ�E���^�I��
			break;

		if(_str[cnt] < 0x30 || _str[cnt] > 0x39)	// �A�X�L�[�R�[�h�̐����łȂ�������
			return 0;

		cnt++;
	}

	while(cnt > 0)
	{
		val += (_str[cnt - 1] - 0x30) * magnifi;
		magnifi *= 10;
		cnt--;
	}

	return val;
}


int decto10(char* _str)
{
	int cnt = 0;
	int val = 0;
	int magnifi = 1;

	// ������̃P�^���J�E���g����
	while(1)
	{
		if(_str[cnt] == 0x00)	// NULL�ŃJ�E���^�I��
			break;

		if(!((_str[cnt] >= '0' && _str[cnt] <= '9') || (_str[cnt] >= 'A' && _str[cnt] <= 'F'))) // 16�i���`�F�b�N
			return 0;

		cnt++;
	}

	while(cnt > 0)
	{
		if(_str[cnt - 1] >= '0' && _str[cnt - 1] <= '9')
		{
			val += (_str[cnt - 1] - 0x30) * magnifi;
		}
		else if(_str[cnt - 1] >= 'A' && _str[cnt - 1] <= 'F')
		{
			val += (_str[cnt - 1] - 0x37) * magnifi;
		}

		magnifi *= 16;
		cnt--;
	}

	return val;
}

// ASCII�R�[�h���o�C�i���ɕϊ�
void asciitobin(char* _str, size_t size)
{
	char tmp[3] = {0,};
	int i;
	for(i = 0; i < size; i += 2)
	{
		tmp[0] = _str[i];
		tmp[1] = _str[i + 1];

		_str[i / 2] = (char)decto10(tmp);
	}

	memset(&_str[size / 2], 0x00, size / 2);
}
