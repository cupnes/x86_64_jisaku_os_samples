#ifndef _FONT_H_
#define _FONT_H_

#define FONT_WIDTH	32
#define FONT_HEIGHT	32

enum FONT_IDX {
	FONT_hira_de = 1,
	FONT_hira_he,
	FONT_hira_n,
	FONT_hira_ni,
	FONT_hira_pe,
	FONT_hira_ru,
	FONT_hira_te,
	FONT_hira_xya,
	FONT_kan_cho,
	FONT_kan_dai = 11,
	FONT_kan_han,
	FONT_kan_hatsu = 14,
	FONT_kan_ji,
	FONT_kan_kami,
	FONT_kan_saku,
	FONT_kan_shin,
	FONT_kan_yu,
	FONT_kan_yuki,
	FONT_kata_chi,
	FONT_kata_fu,
	FONT_kata_ku,
	FONT_kata_ra,
	FONT_kata_ru,
	FONT_kata_su,
	FONT_kata_xtu,
	FONT_space = ' ',
	FONT_exc = '!',
	FONT_hyphen = '-',
	FONT_0 = '0',
	FONT_1 = '1',
	FONT_2 = '2',
	FONT_4 = '4',
	FONT_6 = '6',
	FONT_8 = '8',
	FONT_O = 'O',
	FONT_S = 'S',
	FONT__ = '_',
	FONT_x = 'x',
};

extern const unsigned char font_bitmap[][FONT_HEIGHT][FONT_WIDTH];

#endif
