#include <osunc.h>
#include <fb.h>
#include <font.h>
#include <fbcon.h>
#include <iv.h>
#include <fs.h>

#define NUM_SLIDES	15
#define NUM_PAGES	16

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
	"osunc_14.bgra",	/* Cの配列へ変換 */
	"osunc_15.bgra"		/* 実際に出してみるとこんな感じ。文字の色が変わるよ */
	/* "osunc_07.bgra"	 */	/* (もう一度、新刊と技術書典4とサークル名・配置のスライド)そんなわけで、独自フォントだって持ってるOSを作る本を出しますので、4/22の技術書典4はぜひ"け-52"へにゃぺんてへお越しください！ */
};

struct file *page[NUM_PAGES];

unsigned char current = 0;

#define UNIT	10
#define FC_MAX	255
#define TOP_MARGIN	100
#define BOTTOM_MARGIN	25

unsigned char fc_r = FC_MAX, fc_g = FC_MAX, fc_b = FC_MAX;

void dump_titles(void)
{
	/* 座標計算用変数 */
	unsigned int screen_center_x = fb.hr / 2;
	unsigned int screen_center_y = fb.vr / 2;
	unsigned int str_width_half;
	unsigned int start_x, start_y;

	/* フルスクラッチで作る!(11文字) */
	str_width_half = (FONT_WIDTH * 11) / 2;
	start_x = screen_center_x - str_width_half;
	move_cursor(start_x, TOP_MARGIN);
	char series_title[] = {
		FONT_kata_fu, FONT_kata_ru, FONT_kata_su, FONT_kata_ku,
		FONT_kata_ra, FONT_kata_xtu, FONT_kata_chi, FONT_hira_de,
		FONT_kan_saku, FONT_hira_ru, '!', '\0'};
	puts(series_title);

	/* x86_64自作OS(10文字) */
	str_width_half = (FONT_WIDTH * 10) / 2;
	start_x = screen_center_x - str_width_half;
	move_cursor(start_x, TOP_MARGIN + 40);
	char title[] = {
		'x', '8', '6', '_', '6', '4',
		FONT_kan_ji, FONT_kan_saku, 'O', 'S', '\0'};
	puts(title);

	/* 大神　祐真　著(7文字) */
	str_width_half = (FONT_WIDTH * 7) / 2;
	start_x = screen_center_x - str_width_half;
	start_y = screen_center_y - (FONT_HEIGHT / 2);
	move_cursor(start_x, start_y + 15);
	char author[] = {
		FONT_kan_dai, FONT_kan_kami, ' ', FONT_kan_yu, FONT_kan_shin,
		' ', FONT_kan_cho, '\0'};
	puts(author);

	/* 2018-04-22版(11文字) */
	str_width_half = (FONT_WIDTH * 11) / 2;
	start_x = screen_center_x - str_width_half;
	start_y = fb.vr - ((FONT_HEIGHT + 10) * 2) - BOTTOM_MARGIN;
	move_cursor(start_x, start_y);
	char pub[] = {
		'2', '0', '1', '8', '-', '0', '4', '-', '2', '2', FONT_kan_han,
		'\0'};
	puts(pub);

	/* へにゃぺんて 発行(9文字) */
	str_width_half = (FONT_WIDTH * 9) / 2;
	start_x = screen_center_x - str_width_half;
	start_y = fb.vr - (FONT_HEIGHT + 10) - BOTTOM_MARGIN;
	move_cursor(start_x, start_y);
	char circle[] = {
		FONT_hira_he, FONT_hira_ni, FONT_hira_xya, FONT_hira_pe,
		FONT_hira_n, FONT_hira_te, ' ', FONT_kan_hatsu, FONT_kan_yuki, '\0'};
	puts(circle);
}

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
		break;

	case 'r':
		fc_r = fc_g = fc_b = 0;
		break;
	case 'f':
		fc_r = fc_g = fc_b = FC_MAX;
		break;

	case '1':
		fc_r = FC_MAX;
		break;
	case 'q':
		if (fc_r <= FC_MAX - UNIT)
			fc_r += UNIT;
		else
			fc_r = FC_MAX;
		break;
	case 'a':
		if (fc_r >= UNIT)
			fc_r -= UNIT;
		else
			fc_r = 0;
		break;
	case 'z':
		fc_r = 0;
		break;

	case '2':
		fc_g = FC_MAX;
		break;
	case 'w':
		if (fc_g <= FC_MAX - UNIT)
			fc_g += UNIT;
		else
			fc_g = FC_MAX;
		break;
	case 's':
		if (fc_g >= UNIT)
			fc_g -= UNIT;
		else
			fc_g = 0;
		break;
	case 'x':
		fc_g = 0;
		break;

	case '3':
		fc_b = FC_MAX;
		break;
	case 'e':
		if (fc_b <= FC_MAX - UNIT)
			fc_b += UNIT;
		else
			fc_b = FC_MAX;
		break;
	case 'd':
		if (fc_b >= UNIT)
			fc_b -= UNIT;
		else
			fc_b = 0;
		break;
	case 'c':
		fc_b = 0;
		break;
	}

	if (current == 14) {
		set_fg(fc_r, fc_g, fc_b);
		dump_titles();
	}
}
