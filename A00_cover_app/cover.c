#include <cover.h>
#include <fb.h>
#include <font.h>
#include <fbcon.h>
#include <iv.h>

#define UNIT	10
#define FC_MAX	255

unsigned char fc_r = 0, fc_g = 0, fc_b = 0;

void dump_titles(void)
{
	/* フルスクラッチで作る! */
	move_cursor(80, 50);
	char series_title[] = {
		FONT_kata_fu, FONT_kata_ru, FONT_kata_su, FONT_kata_ku,
		FONT_kata_ra, FONT_kata_xtu, FONT_kata_chi, FONT_hira_de,
		FONT_kan_saku, FONT_hira_ru, '!', '\0'};
	puts(series_title);

	/* x86_64自作OS */
	move_cursor(100, 90);
	char title[] = {
		'x', '8', '6', '_', '6', '4',
		FONT_kan_ji, FONT_kan_saku, 'O', 'S', '\0'};
	puts(title);

	/* 大神　祐真　著 */
	move_cursor(100, 150);
	char author[] = {
		FONT_kan_dai, FONT_kan_kami, ' ', FONT_kan_yu, FONT_kan_shin,
		' ', FONT_kan_cho, '\0'};
	puts(author);

	/* 2018-04-22 版 */
	move_cursor(80, 400);
	char pub[] = {
		'2', '0', '1', '8', '-', '0', '4', '-', '2', '2', ' ',
		FONT_kan_han, '\0'};
	puts(pub);

	/* へにゃぺんて 発行 */
	move_cursor(80, 440);
	char circle[] = {
		FONT_hira_he, FONT_hira_ni, FONT_hira_xya, FONT_hira_pe,
		FONT_hira_n, FONT_hira_te, ' ', FONT_kan_hatsu, FONT_kan_yuki, '\0'};
	puts(circle);
}

void cover_main(void)
{
	/* 背景画像表示 */
	iv_init();
	view(0);		/* ファイルシステム1番目のファイルを使う */

	/* 以降、独自フォントを使った文字の描画 */

	/* 文字色設定 */
	set_fg(fc_r, fc_g, fc_b);

	dump_titles();
}

void cover_kbc_handler(char c)
{
	switch (c) {
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

	set_fg(fc_r, fc_g, fc_b);
	dump_titles();
}
