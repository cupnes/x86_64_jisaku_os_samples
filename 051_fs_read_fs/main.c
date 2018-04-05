#include <x86.h>
#include <intr.h>
#include <pic.h>
#include <fb.h>
#include <kbc.h>
#include <fbcon.h>
#include <fs.h>

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

	/* CPUの割り込み有効化 */
	enable_cpu_intr();

	/* HELLO.TXTとFOO.TXTを1行目のみ読む */
	struct file *hello = open("HELLO.TXT");
	if (hello) {
		puts((char *)hello->name);
		putc(' ');
		puts((char *)hello->data);
	} else {
		puts("HELLO.TXT IS NOT FOUND.");
	}
	puts("\r\n");

	struct file *foo = open("FOO.TXT");
	if (foo) {
		puts((char *)foo->name);
		putc(' ');
		puts((char *)foo->data);
	} else {
		puts("FOO.TXT IS NOT FOUND.");
	}
	puts("\r\n");

	/* haltして待つ */
	while (1)
		cpu_halt();
}
