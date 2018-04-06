#ifndef _FONT_H_
#define _FONT_H_

#define FONT_WIDTH	64
#define FONT_HEIGHT	64

enum FONT_IDX {
        font_4,
        font_6,
        font_8,
        font_O,
        font_S,
        font__,
        font_exc,
        font_hira_de,
        font_hira_ru,
        font_kan_ji,
        font_kan_saku,
        font_kata_chi,
        font_kata_fu,
        font_kata_ku,
        font_kata_ra,
        font_kata_ru,
        font_kata_su,
        font_kata_xtu,
        font_x,
};

extern const unsigned char font_bitmap[][FONT_HEIGHT][FONT_WIDTH];

#endif
