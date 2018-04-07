#ifndef _FONT_H_
#define _FONT_H_

#define FONT_WIDTH	32
#define FONT_HEIGHT	32

enum FONT_IDX {
	FONT_hira_de,
	FONT_hira_ru,
	FONT_kan_ji,
	FONT_kan_saku,
	FONT_kata_chi,
	FONT_kata_fu,
	FONT_kata_ku,
	FONT_kata_ra,
	FONT_kata_ru,
	FONT_kata_su,
	FONT_kata_xtu = 11,
	FONT_exc = '!',
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
