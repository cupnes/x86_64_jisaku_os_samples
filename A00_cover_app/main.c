#include <x86.h>
#include <intr.h>
#include <pic.h>
#include <fb.h>
#include <kbc.h>
#include <fbcon.h>
#include <fs.h>
#include <common.h>
#include <iv.h>
#include <font.h>

void start_kernel(void *_t __attribute__ ((unused)), struct framebuffer *_fb,
		  void *_fs_start)
{
	/* フレームバッファ周りの初期化 */
	fb_init(_fb);
	set_fg(255, 255, 255);
	set_bg(0, 70, 250);
	clear_screen();

	/* CPU周りの初期化 */
	gdt_init();
	intr_init();

	/* 周辺ICの初期化 */
	pic_init();
	kbc_init();

	/* ファイルシステムの初期化 */
	fs_init(_fs_start);

	/* 画像ビューアの初期化 */
	/* iv_init(); */

	/* move_cursor(100, 50); */
	/* フルスクラッチで作る! */
	putc(FONT_kata_fu);
	putc(FONT_kata_ru);
	putc(FONT_kata_su);
	putc(FONT_kata_ku);
	putc(FONT_kata_ra);
	putc(FONT_kata_xtu);
	putc(FONT_kata_chi);
	putc(FONT_hira_de);
	putc(FONT_kan_saku);
	putc(FONT_hira_ru);
	putc('!');

	puts("\r\n");

	putc(FONT_kan_ji);
	putc(FONT_kan_saku);
	putc('O');
	putc('S');

	/* CPUの割り込み有効化 */
	enable_cpu_intr();

	/* haltして待つ */
	while (1)
		cpu_halt();
}
