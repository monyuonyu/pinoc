#include "../../common/typedef.h"
#include "../../common/global.h"
#include "../../lib/string.h"

/* io_hlt32 */
__asm__(
		"io_hlt32:		\n\t"
		"hlt    		\n\t"
		"ret			\n\t"
);

/* LJMP */
//__asm__(
//		"test_cs		=	0x08	\n\t"
//		"test_offset	=	0x00	\n\t"
//		"LJMP:						\n\t"
//		"ljmp	$test_cs,	$test_offset	\n\t"	// セグメント2個め、オフセット0
//);

vo io_write32(si xsize, si ysize, si xSrc, si ySrc, s1 color)
{

	s1* s1_dst = graphicmode.vram;
	s1_dst += graphicmode.xsize * ySrc;
	s1_dst += xSrc;

	si si_i, si_ii;

	FOR(si_i, ysize)
	{
		FOR(si_ii, xsize)
		{
			s1_dst[si_ii] = color;
		}
		s1_dst += graphicmode.xsize;
	}
}

/* セグメントディスクリプタを生成
 31                                      1615                                      00
 ┌─────────────────────┬─────────────────────┐
                  base                               Limit
 ├────────┬─┬─┬─┬─┬────┼─┬──┬─┬───┬─┬────────┤
          base      G  DB  予 AVL  Limit     P  DPL  S   Type  A       Base
 └────────┴─┴─┴─┴─┴────┴─┴──┴─┴───┴─┴────────┘
 ※リトルエンディアンに注意
 */
vo io_sd32(SD* _sd, ui base, ui limit, u1 a, u1 type, u1 s, u1 dpl, u1 p, u1 avl,
		u1 db, u1 g)
{
	memset(_sd, 0x00, sizeof(_sd));

	_sd->g = g;

	_sd->db = db;

	_sd->avl = avl;

	// セグメント存在フラグ
	_sd->p = p;

	// 特権レベル
	_sd->dpl = dpl;

	// ディスクリプタ・タイプ
	_sd->s = s;

	// セグメント・タイプ
	_sd->type = type;

	// アクセス済みフラグ
	_sd->a = a;

}
