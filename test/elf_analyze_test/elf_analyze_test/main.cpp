#include <iostream>
#include <fstream>
using namespace std;
//#include <stdio.h>

// �C��BSD���C�Z���X�g�p

//Elf32_Addr	32bit������������
//Elf32_Half	16bit������������
//Elf32_Off		32bit������������
//Elf32_Sword	32bit�����t������
//Elf32_Word	32bit������������
//
//Elf64_Addr	64bit������������
//Elf64_Half	16bit������������
//Elf64_Off		64bit������������
//Elf64_Sword	32bit�����t������
//Elf64_Word	32bit������������
//Elf64_Xword	64bit������������
//Elf64_Sxword	64bit�����t������


/********************************************************************************
	ELF�w�b�_
********************************************************************************/
// 52byte
struct Elf32_Ehdr {
   unsigned char	chare_ident[16];/* 16byte�̃}�W�b�N�R�[�h */
   unsigned short	e_type;			/* �Ĕz�u�\����s�\����ELF�̌`����\���B */
   unsigned short   e_machine;		/* �t�@�C���ŗv�������A�[�L�e�N�`�� */
   unsigned long    e_version;		/* ELF�t�H�[�}�b�g�̃o�[�W�����Ō��݂�1 */
   unsigned long    e_entry;		/* �v���O�����̃G���g���|�C���g�B�w�薳���Ȃ�0�B */
   unsigned long    e_phoff;		/* �v���O�����w�b�_�e�[�u���̃t�@�C���擪����̃I�t�Z�b�g */
   unsigned long    e_shoff;		/* ���s���ɂ͎g���Ȃ� */
   unsigned long    e_flags;		/* �v���Z�b�T�ŗL�̃t���O */
   unsigned short   e_ehsize;		/* ELF�w�b�_�̃T�C�Y */
   unsigned short   e_phentsize;	/* �v���O�����w�b�_�e�[�u����1�v�f������̃T�C�Y */
   unsigned short   e_phnum;		/* �v���O�����w�b�_�e�[�u���̗v�f�� */
   unsigned short   e_shentsize;	/* ���s���ɂ͎g���Ȃ� */
   unsigned short   e_shnum;		/* ���s���ɂ͎g���Ȃ� */
   unsigned short   e_shstrndx;		/* ���s���ɂ͎g���Ȃ� */
};

// 64byte
struct Elf64_Ehdr {
   unsigned char e_ident[16];
   unsigned short    e_type;
   unsigned short    e_machine;
   unsigned long    e_version;
   unsigned long long    e_entry;
   unsigned long long     e_phoff;
   unsigned long long     e_shoff;
   unsigned long    e_flags;
   unsigned short    e_ehsize;
   unsigned short    e_phentsize;
   unsigned short    e_phnum;
   unsigned short    e_shentsize;
   unsigned short    e_shnum;
   unsigned short    e_shstrndx;
};

/********************************************************************************
	�v���O�����w�b�_�e�[�u��
********************************************************************************/
enum {
   PT_NULL,    /* �g���Ȃ��G���g���ŁA���̃����o�̒l�̈Ӗ��͖���` */
   PT_LOAD,    /* ���s���Ƀ��[�h�����Z�O�����g */
   PT_DYNAMIC, /* ���I�\���̔z���ێ�����Z�O�����g */
   PT_INTERP,  /* �t�@�C���̉��߂Ɏg����C���^�v���^�̃p�X��ێ�����Z�O�����g */
   PT_NOTE,    /* �t�@�C���̉��߂ɂ͎g���Ȃ�����ێ�����Z�O�����g */
   PT_SHLIB,   /* �\�� */
   PT_PHDR,    /* �v���O�����w�b�_�e�[�u���i�v���O�����̃������C���[�W�̈ꕔ�ł���ꍇ�̂ݑ��݁j */
   PT_TLS,     /* �X���b�h�Ǐ��L���̈�̃e���v���[�g */

   PT_LOOS = 0x60000000,
   /* OS�ŗL�̃Z�}���e�B�N�X�ׂ̈ɗ\�񂳂ꂽ�̈� */
   PT_HIOS = 0x6fffffff,

   PT_LOPROC = 0x70000000,
   /* �v���Z�b�T�ŗL�̃Z�}���e�B�N�X�ׂ̈ɗ\�񂳂ꂽ�̈� */
   PT_HIPROC = 0x7fffffff
};

// 32byte
struct Elf32_Phdr {
	unsigned long p_type;   /* �G���g���̃^�C�v */
	unsigned long  p_offset; /* �Ή�����Z�O�����g�̃t�@�C���擪����̃I�t�Z�b�g */
	unsigned long p_vaddr;  /* ��������ł̃Z�O�����g�̑��o�C�g�̉��z�A�h���X */
	unsigned long p_paddr;  /* �����Ԓn�w�肪�K�؂ȃV�X�e���ׂ̈ɗ\��B */
	unsigned long p_filesz; /* �Ή�����Z�O�����g�̃t�@�C���ł̃T�C�Y�B0���B */
	unsigned long p_memsz;  /* �Ή�����Z�O�����g�̃�������ɓW�J���ꂽ���̃T�C�Y�B0���B */
	unsigned long p_flags;  /* �Ή�����Z�O�����g�ɓK�؂ȃt���O�B */
	unsigned long p_align;  /* p_offset��p_vaddr�����̒l�Ŋ������]��͓����� */
	struct Elf32_Phdr* next;
};

// 56byte
struct Elf64_Phdr {
	unsigned long  p_type;
	unsigned long  p_flags;
	unsigned long long   p_offset;
	unsigned long long  p_vaddr;
	unsigned long long  p_paddr;
	unsigned long long p_filesz;
	unsigned long long p_memsz;
	unsigned long long p_align;
	struct Elf64_Phdr* next;
};
/********************************************************************************
	�Z�N�V�����w�b�_�e�[�u��
********************************************************************************/


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
long littletobig(unsigned char* buff, char size)
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

int main()
{
	char* buff = (char*)malloc(1048);

	printf("-------- sizeof --------\n");
	printf("pointer : %t%dbyte\n", sizeof(void*));
	printf("char : %dbyte\n", sizeof(char));
	printf("int : %dbyte\n", sizeof(int));
	printf("short : %dbyte\n", sizeof(short));
	printf("long : %dbyte\n", sizeof(long));
	printf("long long : %dbyte\n", sizeof(long long));


	// elf�T���v���ǂݍ���
	ifstream ifile("sample1.abs", ios::binary);
	ifile.read(buff, 1048);
	ifile.close();

	elf_init(buff);
	elf_status();

	return 0;
}
