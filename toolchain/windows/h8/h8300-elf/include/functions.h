#define and_ccr(mask) asm ("andc.b %0,ccr"::"g"(mask))
#define or_ccr(mask) asm ("orc.b %0,ccr"::"g"(mask))
#define xor_ccr(mask) asm("xorc.b %0,ccr"::"g"(mask))

#if defined __H8300S__ || defined __H8300SX__
#define and_exr(mask) asm ("andc.b %0,exr"::"g"(mask))
#define or_exr(mask) asm ("orc.b %0,exr"::"g"(mask))
#define xor_exr(mask) asm("xorc.b %0,exr"::"g"(mask))
#endif

#define trapa(trap_no) asm ("trapa  %0"::"g"(trap_no))

extern __inline__ void dadd(unsigned char size, char *ptr1, char *ptr2,char *rst) __attribute__ ((always_inline));
extern __inline__ void eepmov(char *src, char *dest, unsigned char count) __attribute__ ((always_inline));
extern __inline__ void dsub(unsigned char size, char *ptr1, char *ptr2,char *rst) __attribute__ ((always_inline));
extern __inline__ unsigned char get_imask_ccr(void) __attribute__ ((always_inline));
extern __inline__ unsigned char get_imask_exr(void) __attribute__ ((always_inline));
extern __inline__ void mac(long val, int *ptr1, int *ptr2, unsigned long count) __attribute__ ((always_inline));
extern __inline__ void nop(void) __attribute__ ((always_inline));
extern __inline__ unsigned char get_ccr(void) __attribute__ ((always_inline));
extern __inline__ unsigned char get_exr(void) __attribute__ ((always_inline));
extern __inline__ int rotlw(int count, int data) __attribute__ ((always_inline));
extern __inline__ void set_imask_ccr(unsigned char mask) __attribute__ ((always_inline));
extern __inline__ void set_imask_exr(unsigned char mask) __attribute__ ((always_inline));
extern __inline__ void sleep(void) __attribute__ ((always_inline));
extern __inline__ void tas(char *addr) __attribute__ ((always_inline));
extern __inline__ void set_ccr(unsigned char value) __attribute__ ((always_inline));
extern __inline__ void set_exr(unsigned char value) __attribute__ ((always_inline));
extern __inline__ void ovfaddw(int dst,int src,int *rst) __attribute__ ((always_inline));
extern __inline__ void ovfsubw(int dst,int src,int *rst) __attribute__ ((always_inline));
extern __inline__ void ovfshllul(unsigned long dst,unsigned long *rst) __attribute__ ((always_inline));
extern __inline__ void ovfshalw(int dst,int *rst) __attribute__ ((always_inline));
extern __inline__ void ovfnegw(int dst,int *rst) __attribute__ ((always_inline));
extern __inline__ void set_vbr(long data) __attribute__ ((always_inline));

#if defined __H8300S__ || defined __H8300SX__

extern __inline__ unsigned char get_imask_exr(void){
       unsigned char imask;
       asm("stc exr,r0l":::"r0");
       asm("and.b #0x07,r0l");
       asm("mov.b r0l, %0l":"=g"(imask));
       return(imask);
}
extern __inline__ void set_imask_exr (unsigned char mask)
{
	switch(mask)
	{
		case 0 : asm("andc.b #0xf8, exr");
				 break;
		case 7 : asm("orc.b #0x07, exr");
				 break;
		default: asm("stc exr,r0h");
				 asm("and.b #0xf8, r0h");
				 asm("mov %0l, r0l"::"r"(mask));
				 asm("or.b r0l,r0h");
				 asm("ldc r0h,exr");
				 break;
	}
}
extern __inline__ void mac(long val, int *ptr1, int *ptr2, unsigned long count){
	asm ("mov.l %0,er2"::"g"(count):"er2");
	asm ("mov.l %0,er3"::"g"(ptr1):"er3");
	asm ("mov.l %0,er0"::"g"(ptr2):"er0");
	asm ("mov.l %0,er1"::"g"(val):"er1");
	asm ("clrmac");
	asm ("ldmac er1,macl");
	asm ("mov.l er2,er2\n\t"
		 "beq 2f\n1:\n\t"
		 "mac @er0+,@er3+\n\t"
		 "dec.l #1,er2\n\t"
		 "bne 1b\n2:"
		);
	asm ("stmac  macl,er2");
}
extern __inline__ unsigned char get_exr(void){
	unsigned char exr_val;
	asm("stc exr,r0l":::"r0");
	asm("mov.b r0l, %0l":"=g"(exr_val));
	return(exr_val);
}
extern __inline__ void set_exr(unsigned char value){
	asm("mov.b %0l,r0l"::"r"(value):"r0");
	asm("ldc r0l, exr");
}
extern __inline__ void tas(char *addr)
{
#ifndef __NORMAL_MODE__
	asm("mov.l %0, er1"::"r"(addr):"er1");
	asm("tas @er1");
#endif
}
#endif

extern __inline__ void dadd(unsigned char size, char *ptr1, char *ptr2,char *rst)
   {
 	asm ("mov.b %0l,r4l"::"r"(size):"r4");
#if defined __H8300__ || defined __NORMAL_MODE__
   	asm ("mov.w %0,r3"::"r"(ptr1):"r3");
   	asm ("mov.w %0,r5"::"r"(ptr2):"r5");
   	asm ("mov.w %0,r1"::"r"(rst):"r1");
   	asm ("andc #0xde:8, ccr\n\t"
   	     "1: \n\t"
   	     "mov.b @r3+, r0l\n\t "
   	     "mov.b @r5+, r2l\n\t "
  	     "addx.b r2l, r0l\n\t"
   	     "daa r0l\n\t"
   	     "mov.b r0l,@r1\n\t"
   	     "inc #1,r1\n\t"
   	     "dec.b  r4l\n\t"
   	     "bne 1b\n\t"
  	    );
#else
   	asm ("mov.l %0,er3"::"r"(ptr1):"er3");
   	asm ("mov.l %0,er5"::"r"(ptr2):"er5");
   	asm ("mov.l %0,er1"::"r"(rst):"er1");
   	asm ("andc #0xde:8, ccr\n\t"
  		 "1: \n\t"
   	     "mov.b @er3+, r0l\n\t "
   	     "mov.b @er5+, r2l\n\t "
  	     "addx.b r2l, r0l\n\t"
   	     "daa r0l\n\t"
   	     "mov.b r0l,@er1\n\t"
   	     "inc.l #1,er1\n\t"
   	     "dec.b  r4l\n\t"
   	     "bne 1b\n\t"
  	    );
#endif
 }
extern __inline__ void eepmov(char *src, char *dest, unsigned char count){
	asm("mov.b %0l,r4l"::"r"(count):"r4");
	asm("extu.w r4");

#if defined __H8300__ || defined __NORMAL_MODE__
	asm("mov.w %0,r5"::"r"(src):"r5");
	asm("push r6");
	asm("mov.w %0,r6"::"r"(dest):"r6");
	asm("eepmov");
	asm("pop r6");
#else
	asm("mov.l %0,er5"::"r"(src):"er5");
	asm("push er6");
	asm("mov.l %0,er6"::"r"(dest):"er6");
	asm("eepmov");
	asm("pop er6");
#endif
}
extern __inline__ void dsub(unsigned char size, char *ptr1, char *ptr2,char *rst)
  {
	asm ("mov.b %0l,r4l"::"r"(size):"r4");
#if defined __H8300__ || defined __NORMAL_MODE__
   	asm ("mov.w %0,r3"::"r"(ptr1):"r3");
   	asm ("mov.w %0,r5"::"r"(ptr2):"r5");
   	asm ("mov.w %0,r1"::"r"(rst):"r1");
   	asm ("andc #0xde:8, ccr\n\t"
  		 "1: \n\t"
   	     "mov.b @r3+, r0l\n\t "
   	     "mov.b @r5+, r2l\n\t "
  	     "subx.b r2l, r0l\n\t"
   	     "das r0l\n\t"
   	     "mov.b r0l,@r1\n\t"
   	     "inc #1,r1\n\t"
   	     "dec.b  r4l\n\t"
   	     "bne 1b\n\t"
  	    );
#else
  	asm ("mov.l %0,er3"::"r"(ptr1):"er3");
  	asm ("mov.l %0,er5"::"r"(ptr2):"er5");
  	asm ("mov.l %0,er1"::"r"(rst):"er1");
  	asm ("andc #0de, ccr\n\t"
 		 "1: \n\t"
  	     "mov.b @er3+, r0l\n\t "
  	     "mov.b @er5+, r2l\n\t "
 	     "subx.b r2l, r0l\n\t"
  	     "das r0l\n\t"
  	     "mov.b r0l,@er1\n\t"
  	     "inc.l #1,er1\n\t"
  	     "dec.b  r4l\n\t"
  	     "bne 1b\n\t"
 	    );
#endif
}
extern __inline__ unsigned char get_imask_ccr(void){
	unsigned char imask;
	asm("stc ccr,r0l":::"r0");
	asm("and.b #0x80,r0l");
	asm("rotl.b r0l");
	asm("mov.b r0l, %0l":"=g"(imask));
	return(imask);
}
extern __inline__ void nop(void){

   asm ("nop");
}
extern __inline__ unsigned char get_ccr(void){
	unsigned char ccr_val;
	asm("stc ccr,r0l":::"r0");
	asm("mov.b r0l, %0l":"=g"(ccr_val));
	return(ccr_val);
}
extern __inline__ int rotlw(int count, int data)
{
	int ires;
	asm("mov.w %0,r0"::"r"(count):"r0");
	asm("mov.w %0,r1"::"r"(data):"r1");
	asm("mov.w r0, r0");
	asm("beq 2f\n"
	    " 1:\n\t"
	    "rotl.w r1\n\t"
	    "dec.w #1, r0\n\t"
	    "bne 1b\n"
	    "2:"
	   );
    asm("mov.w r1, %0":"=g"(ires));
    return(ires);
}
extern __inline__ void set_imask_ccr(unsigned char mask)
{
    if(mask==1) 
	    /* mask = 1, sets the Interrupt mask bit, this will disable interrupts except NMI */
		asm("orc.b #0x80, ccr"); 
	else
		/* mask = 0, resets the Interrupt mask bit, this will enable interrupts*/
		asm("andc.b #0x7f, ccr"); 
}
extern __inline__ void sleep(void){
     asm("sleep");
}

extern __inline__ void set_ccr(unsigned char value){
	asm("mov.b %0l,r0l"::"r"(value):"r0");
	asm("ldc r0l, ccr");
}
extern __inline__ void ovfaddw(int dst,int src,int *rst)
{
	asm ("mov.w %0, r0"::"r"(src):"r0");
	asm ("mov.w %0, r1"::"r"(dst):"r1");
	asm ("add.w r1, r0");
	asm ("stc ccr, r1l":::"r1");
	asm ("mov.w r0, @%0"::"r"(rst));
	asm ("ldc r1l, ccr");
}
extern __inline__ void ovfsubw(int dst,int src,int *rst)
{
	asm ("mov.w %0, r0"::"r"(src):"r0");
	asm ("mov.w %0, r1"::"r"(dst):"r1");
	asm ("sub.w r1, r0");
	asm ("stc ccr, r1l":::"r1");
	asm ("mov.w r0, @%0"::"r"(rst));
	asm ("ldc r1l, ccr");
}
extern __inline__ void ovfshllul(unsigned long dst,unsigned long *rst)
{
	asm ("mov.l %0, er1"::"r"(dst):"er1");
	asm ("shal.l er1");
	asm ("stc ccr, r1l":::"r1");
	asm ("mov.l er1, @%0"::"r"(rst));
	asm ("ldc r1l, ccr");
}
extern __inline__ void  ovfshalw(int dst,int *rst)
{
	asm ("mov.w %0, r0"::"r"(dst):"r0");
	asm ("shal.w r0");
	asm ("stc ccr, r1l":::"r1");
	asm ("mov.w r0, @%0"::"r"(rst));
	asm ("ldc r1l, ccr");
}
extern __inline__ void ovfnegw(int dst,int *rst)
{
	asm ("mov.w %0, r0"::"r"(dst):"r0");
	asm ("not.w r0");
	asm ("add.w #1, r0");
	asm ("stc ccr, r1l":::"r1");
	asm ("mov.w r0, @%0"::"r"(rst));
	asm ("ldc r1l, ccr");
}

extern __inline__ void set_vbr(long data)
{
	
	asm("mov.l %0,er1"::"r"(data):"er1");
	
	/* Rotate left 12 times since low 
	   12 bits of VBR are always ignored*/
	asm("mov.l #0x0C, er0");
	asm("mov.w r0, r0");
	asm("1:\n\t"
	    "rotl er1\n\t"
	    "dec.w #1, r0\n\t"
	    "bne 1b\n"
	   );	
	
	/*
	Use the ldc instruction to load the value
	from er1 into vbr
	*/
	asm("ldc er1,vbr");
}














