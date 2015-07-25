#include "../../../common/typedef.h"
#include "../head/realmode.h"

vo io_load16();
vo io_debug16();

/*******************************************************************************
 		スタックの初期化
 *******************************************************************************/
__asm__(
		".text						\n\t"
		"movw	$0x0400, 	%ax		\n\t"
		"movw	%ax,		%ss		\n\t"
		"movl	$0x0,		%eax	\n\t"
		"movl	%eax,		%esp	\n\t"
		"movl	%eax,		%ebp	\n\t"
);

/*******************************************************************************
 		メイン関数
 *******************************************************************************/
void main16()
{
	// ブートローダを0x5000番地へ配置
	io_load16();

//#if DEBUG
//	io_debug16();
//#endif

	// 関数の途中で抜けるのでスタックを戻しておく
	__asm__("popl	%ebx");


	/*--------------------------------------------------------------------------------
			 ブートローダへjamp
	 --------------------------------------------------------------------------------*/
	__asm__("jmp	0x5000");

}

/*******************************************************************************
 		サブ関数
 *******************************************************************************/
//vo io_debug16()	// 画面に何か１つ表示します
//{
//
//	__asm__(
//			"pushw	%ax				\n\t"
//			"movb	$0x0e,	%ah		\n\t"
//			"movb	$1,		%al		\n\t"
//			"int	$0x10			\n\t"
//			"popw	%ax				\n\t"
//	);
//}

// フロッピーディスクからBIOSの力を借りてデータを読み込みます
// biosがつかえなくなったらドライバの力を...
vo io_load16()
{
	__asm__(
			"movw	$0x500,	%di		\n\t"
			"movw	%di,		%es		\n\t"
			"movw    $0x00,     %bx  \n\t"

			"movb    $0x00,     %ch  \n\t"
			"movb    $0x00,     %dh  \n\t"
			"movb    $0x02,     %cl  \n\t"

			"movw    $0x00,     %si  \n\t" // 失敗カウンタ初期化

			"io_load_retry:          \n\t"

			"movb    $0x02,     %ah  \n\t"
			"movb    $0x08,     %al  \n\t" // 連続したセクタr
			"movb    $0x00,     %dl  \n\t"
			"int     $0x13           \n\t" //	セクタ読み込み[bios]

			"jnc     io_load_success	\n\t"

			"add     $0x01,     %si  \n\t" //	失敗回数をカウントアップ
			"cmp     $0x05,     %si  \n\t" // 5回失敗したらエラー終了
			"jae     io_load_error   \n\t"

			"movb    $0x00,     %ah  \n\t"
			"movb    $0x00,     %dl  \n\t"
			"int     $0x13           \n\t"
			"jmp     io_load_retry   \n\t" //	初期化してリトライ
	);

	__asm__("io_load_error:");
#if DEBUG
//	io_debug16();
#endif

	__asm__("io_load_success:");
#if DEBUG
//	io_debug16();
#endif

}
