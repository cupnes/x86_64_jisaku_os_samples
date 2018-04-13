#include <osunc.h>
#include <fb.h>
#include <font.h>
#include <fbcon.h>
#include <iv.h>
#include <fs.h>

#define NUM_SLIDES	14
#define NUM_PAGES	15

char *slide[NUM_SLIDES] = {
	"osunc_01.bgra",	/* タイトル */
	"osunc_02.bgra",	/* 自己紹介 */
	"osunc_03.bgra",	/* OCOS5表紙&アーキテクチャ図(一昨年) */
	"osunc_04.bgra",	/* UBMP表紙(去年@osunc lt) */
   	"osunc_05.bgra",	/* "ブートローダー" on UBMP表紙(薄く)(「UBMPでは結局UEFIファームウェアに助けてもらうブートローダー」) */
	"osunc_06.bgra",	/* x86jo(表紙) */
	"osunc_07.bgra",	/* tbf4出します */
	"osunc_08.bgra",	/* x86jo(アーキテクチャ図) */
	"osunc_09.bgra",	/* 「フォント」に丸を付ける『機能的に増えたのはここだけ。。。(UEFI終了後の世界なので丸々すべて実装しているけど)』 */
	"osunc_10.bgra",	/* 独自フォントの作り方！ */
	"osunc_11.bgra",	/* まず、使いたい文字を紙に書きます */
	"osunc_12.bgra",	/* 1文字ずつの画像ファイルへ分割します */
	"osunc_13.bgra",	/* ImageMagickで変換します(シェル芸)、そんな苦労の末 */
	"osunc_14.bgra"		/* Cの配列へ変換 */
	/* "osunc_07.bgra"	 */	/* (もう一度、新刊と技術書典4とサークル名・配置のスライド)そんなわけで、独自フォントだって持ってるOSを作る本を出しますので、4/22の技術書典4はぜひ"け-52"へにゃぺんてへお越しください！ */
};

struct file *page[NUM_PAGES];

unsigned char current = 0;

void osunc_main(void)
{
	unsigned char i;
	for (i = 0; i < NUM_SLIDES; i++)
		page[i] = open(slide[i]);
	page[i] = page[6];

	/* 背景画像表示 */
	view(page[current]);
}

void osunc_kbc_handler(char c)
{
	switch (c) {
	case 'j':
		if (current < NUM_PAGES - 1)
			view(page[++current]);
		break;
	case 'k':
		if (current > 0)
			view(page[--current]);
	}
}
