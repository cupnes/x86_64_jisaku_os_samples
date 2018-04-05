#ifndef _FB_H_
#define _FB_H_

struct pixelformat {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char _reserved;
};

struct framebuffer {
	struct pixelformat *base;
	unsigned long long size;
	unsigned int hr;
	unsigned int vr;
};

extern struct framebuffer fb;

void fb_init(struct framebuffer *_fb);
void set_fg(unsigned char r, unsigned char g, unsigned char b);
void set_bg(unsigned char r, unsigned char g, unsigned char b);
inline void draw_px(unsigned int x, unsigned int y,
		    unsigned char r, unsigned char g, unsigned char b);
inline void draw_px_fg(unsigned int x, unsigned int y);
inline void fill_rect(unsigned int x, unsigned int y,
		      unsigned int w, unsigned int h,
		      unsigned char r, unsigned char g, unsigned char b);
void clear_screen(void);

#endif
