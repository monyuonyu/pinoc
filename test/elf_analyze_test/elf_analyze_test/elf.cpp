
#include "elf.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static unsigned char m_magic[4];
static unsigned char m_fileclass;
static unsigned char m_endian;
static unsigned char m_elf_version;
static unsigned char m_os_abi;
static unsigned char m_abi_version;
static unsigned short m_e_type;
static unsigned short m_e_machine;
static unsigned long m_e_version;
static unsigned long m_e_entry;
static unsigned long m_e_phoff;
static unsigned long m_e_shoff;
static unsigned long m_e_flags;
static unsigned short m_e_ehsize;
static unsigned short m_e_phentsize;
static unsigned short m_e_phnum;
static unsigned short m_e_shentsize;
static unsigned short m_e_shnum;
static unsigned short m_e_shstrndx;
static struct Elf32_Phdr* m_program_hed;

// 32bit�܂�
static long littletobig(unsigned char* buff, char size)
{
	unsigned long tmp = 0;
	unsigned long scale = 1;
	int i;
	
	for(i = size - 1; i >= 0; i--)
	{
		tmp += buff[i] * scale;
		scale *= 0x100;
	}

	//tmp += buff[0] * 0x1000000;
	//tmp += buff[1] * 0x10000;
	//tmp += buff[2] * 0x100;
	//tmp += buff[3];

	//printf("ltob 0x%x\n", tmp);

	return tmp;
}

void elf_status()
{
	int i;
	struct Elf32_Phdr* elf_program_ent;

	printf("-------- elf_status --------\n");

	printf("---- ELF Header ----\n");
	// �}�W�b�N
	printf("magic : %x%c%c%c\n", m_magic[0], m_magic[1], m_magic[2], m_magic[3]);
	printf("�t�@�C���N���X : %d\n", m_fileclass);
	printf("�G���f�B�A�� : %d\n", m_endian);
	printf("elf version : %d\n", m_elf_version);
	printf("OS ABI : %d\n", m_os_abi);
	printf("ABI version : %d\n", m_abi_version);
	// e_ident[9...15]	���g�p
	printf("�Ĕz�u�\����s�\����ELF�̌`����\���B : 0x%x\n", m_e_type);
	printf("�t�@�C���ŗv�������A�[�L�e�N�`�� : 0x%x\n", m_e_machine);
	printf("ELF�t�H�[�}�b�g�̃o�[�W�����Ō��݂�1 : 0x%x\n", m_e_version);
	printf("�v���O�����̃G���g���|�C���g�B�w�薳���Ȃ�0 : 0x%x\n", m_e_entry);
	printf("�v���O�����w�b�_�e�[�u���̃t�@�C���擪����̃I�t�Z�b�g : %dbyte\n", m_e_phoff);
	printf("���s���ɂ͎g���Ȃ� : 0x%x\n", m_e_shoff);
	printf("�v���Z�b�T�ŗL�̃t���O : 0x%x\n", m_e_flags);
	printf("ELF�w�b�_�̃T�C�Y : %dbyte\n", m_e_ehsize);
	printf("�v���O�����w�b�_�e�[�u����1�v�f������̃T�C�Y : %dbyte\n", m_e_phentsize);
	printf("�v���O�����w�b�_�e�[�u���̗v�f�� : %d��\n", m_e_phnum);
	printf("���s���ɂ͎g���Ȃ� : 0x%x\n", m_e_shentsize);
	printf("���s���ɂ͎g���Ȃ� : 0x%x\n", m_e_shnum);
	printf("���s���ɂ͎g���Ȃ� : 0x%x\n", m_e_shstrndx);

	printf("---- Program Header ----\n");
	elf_program_ent = m_program_hed;
	// �v���O�����w�b�_�[�̌����J��Ԃ�
	for(i = 0; i < m_e_phnum; i++)
	{
		printf("�� Program Header %d\n", i+1);
		
		printf("1.�G���g���̃^�C�v : 0x%x\n", elf_program_ent->p_type);
		printf("2.�Ή�����Z�O�����g�̃t�@�C���擪����̃I�t�Z�b�g : %dbyte\n", elf_program_ent->p_offset);
		printf("3.��������ł̃Z�O�����g�̑��o�C�g�̉��z�A�h���X : 0x%x\n", elf_program_ent->p_vaddr);
		printf("4.�����Ԓn�w�肪�K�؂ȃV�X�e���ׂ̈ɗ\�� : 0x%x\n", elf_program_ent->p_paddr);
		printf("5.�Ή�����Z�O�����g�̃t�@�C���ł̃T�C�Y�B0���� : %dbyte\n", elf_program_ent->p_filesz);
		printf("6.�Ή�����Z�O�����g�̃�������ɓW�J���ꂽ���̃T�C�Y�B0���� : %dbyte\n", elf_program_ent->p_memsz);
		printf("7.�Ή�����Z�O�����g�ɓK�؂ȃt���O : 0x%x\n", elf_program_ent->p_flags);
		printf("8.p_offset�u2.�v��p_vaddr�u3.�v�����̒l�Ŋ������]��͓����� : 0x%x\n", elf_program_ent->p_align);

		elf_program_ent = elf_program_ent->next;
	}
}

int elf_check(struct Elf32_Ehdr* buff)
{
	//e_ident[0]	magic	0x7f
	//e_ident[1]	magic	'E'
	//e_ident[2]	magic	'L'
	//e_ident[3]	magic	'F'
	//e_ident[4]	�t�@�C���̃N���X	0=invalid, 1=32bit, 2=64bit
	//e_ident[5]	�f�[�^�̕����������i�G���f�B�A�����j	0=invalid, 1=LSB, 2=MSB
	//e_ident[6]	ELF�w�b�_�̃o�[�W����	���݂�1
	//e_ident[7]	�t�@�C�����ΏۂƂ���OS��ABI	
	//e_ident[8]	�t�@�C�����ΏۂƂ���ABI�̃o�[�W����	
	//e_ident[9...15]	���g�p
	
	int check_flg = 0;
	
	printf("-------- elf_check --------\n");
	
	// magic�R�[�h���Ԉ���Ă����ELF�t�@�C���ł͂Ȃ��Ɣ��f
	if(buff->chare_ident[0] != 0x7F) check_flg = 1;
	if(buff->chare_ident[1] != 'E') check_flg = 1;
	if(buff->chare_ident[2] != 'L') check_flg = 1;
	if(buff->chare_ident[3] != 'F') check_flg = 1;

	if(check_flg)
	{
		printf("������ELF�t�@�C���t�H�[�}�b�g�ł͂���܂���\n");
		return 1;
	}
	printf("������ELF�t�@�C���t�H�[�}�b�g�ł�\n");
	return 0;
}


// elf�t�@�C������͂��ď���������
int elf_init(char* buff)
{
	int i;
	struct Elf32_Phdr* ent,* ent_tmp;
	struct Elf32_Ehdr* elf_header;
	struct Elf32_Phdr* elf_program;

	printf("-------- elf_init --------\n");
	elf_header = (struct Elf32_Ehdr*)buff;
	if(elf_check(elf_header))
		return 1;

	m_magic[0] = elf_header->chare_ident[0];
	m_magic[0] = elf_header->chare_ident[1];
	m_magic[0] = elf_header->chare_ident[2];
	m_magic[0] = elf_header->chare_ident[3];
	m_fileclass = elf_header->chare_ident[4];
	m_endian =  elf_header->chare_ident[5];
	m_elf_version = elf_header->chare_ident[6];
	m_os_abi = elf_header->chare_ident[7];
	m_abi_version = elf_header->chare_ident[8];
	// e_ident[9...15]	���g�p
	m_e_type = littletobig((unsigned char*)&elf_header->e_type, 2);
	m_e_machine = littletobig((unsigned char*)&elf_header->e_machine, 2);
	m_e_version = littletobig((unsigned char*)&elf_header->e_version, 4);
	m_e_entry = littletobig((unsigned char*)&elf_header->e_entry, 4);
	m_e_phoff = littletobig((unsigned char*)&elf_header->e_phoff, 4);
	m_e_shoff = littletobig((unsigned char*)&elf_header->e_shoff, 4);
	m_e_flags = littletobig((unsigned char*)&elf_header->e_flags, 4);
	m_e_ehsize =  littletobig((unsigned char*)&elf_header->e_ehsize, 2);
	m_e_phentsize = littletobig((unsigned char*)&elf_header->e_phentsize, 2);
	m_e_phnum =  littletobig((unsigned char*)&elf_header->e_phnum, 2);
	m_e_shentsize = littletobig((unsigned char*)&elf_header->e_shentsize, 2);
	m_e_shnum = littletobig((unsigned char*)&elf_header->e_shnum, 2);
	m_e_shstrndx = littletobig((unsigned char*)&elf_header->e_shstrndx, 2);

	// �v���O�����w�b�_�̐��͕s��Ȃ̂Ń��X�g�\���ŕێ�����
	ent = (struct Elf32_Phdr*)malloc(sizeof(struct Elf32_Phdr));
	m_program_hed = ent;

	// �v���O�����w�b�_�[�̌����J��Ԃ�
	for(i = 0; i < m_e_phnum; i++)
	{
		// �v���O�����w�b�_�̊J�n�Ԓn�擾
		elf_program = (struct Elf32_Phdr*)&buff[ m_e_phoff + m_e_phentsize * i ];
		
		// �w�b�_�̓��e��ۑ�
		ent->p_type = littletobig((unsigned char*)&elf_program->p_type, 4);
		ent->p_offset = littletobig((unsigned char*)&elf_program->p_offset, 4);
		ent->p_vaddr = littletobig((unsigned char*)&elf_program->p_vaddr, 4);
		ent->p_paddr = littletobig((unsigned char*)&elf_program->p_paddr, 4);
		ent->p_filesz = littletobig((unsigned char*)&elf_program->p_filesz, 4);
		ent->p_memsz = littletobig((unsigned char*)&elf_program->p_memsz, 4);
		ent->p_flags = littletobig((unsigned char*)&elf_program->p_flags, 4);
		ent->p_align = littletobig((unsigned char*)&elf_program->p_align, 4);
		ent->next = 0x00; // ���X�g�̏I�[�R�[�h 0x00

		// ���X�g�\���ŕۑ�����
		ent_tmp = ent;
		ent = (struct Elf32_Phdr*)malloc(sizeof(struct Elf32_Phdr));
		ent_tmp->next = ent;
	}


	return 0;
}

void* elf_devlop(char* buff)
{
	int i;
	long virtual_space_cnt;
	void* entry_point;
	struct Elf32_Phdr* ent;

	int test_buff = (int)(char*)malloc(1000);	// �e�X�g�o�b�t�@�uvisual studio��ł̂ݕK�v�v

	// elf_�w�b�_�[�ɃG���g���|�C���g�������Ă������ꍇ�͗D��I�ɓK��
	if(m_e_entry)
	{
		entry_point = (void*)m_e_entry;
	}
	else // �v���O�����w�b�_�̊J�n�Ԓn��K��
	{
		entry_point = (void*)m_program_hed->p_vaddr;
	}

	ent = m_program_hed;

	// �v���O�����w�b�_�̗v�f��S�ēW�J����
	for(i = 0; i < m_e_phnum; i++)
	{
		virtual_space_cnt = ent->p_memsz - ent->p_filesz;
		memcpy((void*)(test_buff+(ent->p_vaddr)), &buff[ent->p_offset], ent->p_filesz);
		memset((void*)(test_buff+(ent->p_vaddr) + ent->p_filesz), 0x00, virtual_space_cnt);
		//memcpy((void*)((ent->p_vaddr)), &buff[ent->p_offset], ent->p_filesz);
		//memset((void*)((ent->p_vaddr) + ent->p_filesz), 0x00, virtual_space_cnt);
		ent = ent->next;
	}

	

	return entry_point;
}