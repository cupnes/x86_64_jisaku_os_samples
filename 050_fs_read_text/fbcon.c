#include <fbcon.h>
#include <fb.h>
#include <font.h>

unsigned int cursor_x = 0, cursor_y = 0;

void putc(char c)
{
	unsigned int x, y;

	switch(c) {
	case '\r':
		cursor_x = 0;
		break;

	case '\n':
		cursor_y += FONT_HEIGHT;
		if ((cursor_y + FONT_HEIGHT) >= fb.vr) {
			cursor_x = cursor_y = 0;
			clear_screen();
		}
		break;

	default:
		/* カーソル座標(cursor_x,cursor_y)へ文字を描画 */
		for (y = 0; y < FONT_HEIGHT; y++)
			for (x = 0; x < FONT_WIDTH; x++)
				if (font_bitmap[(unsigned int)c][y][x])
					draw_px_fg(cursor_x + x, cursor_y + y);

		/* カーソル座標の更新 */
		cursor_x += FONT_WIDTH;
		if ((cursor_x + FONT_WIDTH) >= fb.hr) {
			cursor_x = 0;
			cursor_y += FONT_HEIGHT;
			if ((cursor_y + FONT_HEIGHT) >= fb.vr) {
				cursor_x = cursor_y = 0;
				clear_screen();
			}
		}
	}
}

void puts(char *s)
{
	while (*s != '\0')
		putc(*s++);
}
