#include <fb.h>

struct framebuffer fb;
struct pixelformat color_bg;

void fb_init(struct framebuffer *_fb)
{
	fb.base = _fb->base;
	fb.size = _fb->size;
	fb.hr = _fb->hr;
	fb.vr = _fb->vr;
}

void set_bg(unsigned char r, unsigned char g, unsigned char b)
{
	color_bg.b = b;
	color_bg.g = g;
	color_bg.r = r;
}

inline void draw_px(unsigned int x, unsigned int y,
		    unsigned char r, unsigned char g, unsigned char b)
{
	struct pixelformat *p = fb.base;
	p += y * fb.hr + x;

	p->b = b;
	p->g = g;
	p->r = r;
}

inline void fill_rect(unsigned int x, unsigned int y,
		      unsigned int w, unsigned int h,
		      unsigned char r, unsigned char g, unsigned char b)
{
	unsigned int i, j;
	for (i = y; i < (y + h); i++)
		for (j = x; j < (x + w); j++)
			draw_px(j, i, r, g, b);
}

void clear_screen(void)
{
	fill_rect(0, 0, fb.hr, fb.vr, color_bg.r, color_bg.g, color_bg.b);
}
