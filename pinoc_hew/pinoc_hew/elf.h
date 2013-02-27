#ifndef _ELF_H_
#define _ELF_H_


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
//struct Elf64_Ehdr {
//   unsigned char e_ident[16];
//   unsigned short    e_type;
//   unsigned short    e_machine;
//   unsigned long    e_version;
//   unsigned long long    e_entry;
//   unsigned long long     e_phoff;
//   unsigned long long     e_shoff;
//   unsigned long    e_flags;
//   unsigned short    e_ehsize;
//   unsigned short    e_phentsize;
//   unsigned short    e_phnum;
//   unsigned short    e_shentsize;
//   unsigned short    e_shnum;
//   unsigned short    e_shstrndx;
//};

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
//struct Elf64_Phdr {
//	unsigned long  p_type;
//	unsigned long  p_flags;
//	unsigned long long   p_offset;
//	unsigned long long  p_vaddr;
//	unsigned long long  p_paddr;
//	unsigned long long p_filesz;
//	unsigned long long p_memsz;
//	unsigned long long p_align;
//	struct Elf64_Phdr* next;
//};



void elf_status();
int elf_check(struct Elf32_Ehdr* buff);
int elf_init(char* buff);
void* elf_devlop(char* buff);

#endif
