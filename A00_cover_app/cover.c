#include <cover.h>
#include <font.h>
#include <fbcon.h>

void cover_main(void)
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

	/* 2018-04-22 版 へにゃぺんて 発行 */
	move_cursor(80, 440);
	char pub[] = {
		'2', '0', '1', '8', '-', '0', '4', '-', '2', '2', ' ',
		FONT_kan_han, ' ', FONT_hira_he, FONT_hira_ni, FONT_hira_xya,
		FONT_hira_pe, FONT_hira_n, FONT_hira_te, ' ', FONT_kan_hatsu,
		FONT_kan_yuki};
	puts(pub);
}
