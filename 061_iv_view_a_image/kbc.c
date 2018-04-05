#include <kbc.h>
#include <x86.h>
#include <fbcon.h>
#include <intr.h>
#include <pic.h>

#define KBC_DATA_ADDR		0x0060
#define KBC_DATA_BIT_IS_BRAKE	0x80
#define KBC_STATUS_ADDR		0x0064
#define KBC_STATUS_BIT_OBF	0x01
#define KBC_INTR_NO		33

const char keymap[] = {
	0x00, ASCII_ESC, '1', '2', '3', '4', '5', '6',
	'7', '8', '9', '0', '-', '^', ASCII_BS, ASCII_HT,
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
	'o', 'p', '@', '[', '\n', 0x00, 'a', 's',
	'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
	':', 0x00, 0x00, ']', 'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',', '.', '/', 0x00, '*',
	0x00, ' ', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '7',
	'8', '9', '-', '4', '5', '6', '+', '1',
	'2', '3', '0', '.', 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, '_', 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, '\\', 0x00, 0x00
};

void kbc_handler(void);

unsigned char get_kbc_data(void)
{
	/* ステータスレジスタのOBFがセットされるまで待つ */
	while (!(io_read(KBC_STATUS_ADDR) & KBC_STATUS_BIT_OBF));

	return io_read(KBC_DATA_ADDR);
}

unsigned char get_keycode(void)
{
	unsigned char keycode;

	/* make状態(brakeビットがセットされていない状態)まで待つ */
	while ((keycode = get_kbc_data()) & KBC_DATA_BIT_IS_BRAKE);

	return keycode;
}

char getc(void)
{
	return keymap[get_keycode()];
}

void do_kbc_interrupt(void)
{
	/* ステータスレジスタのOBFがセットされていなければreturn */
	if (!(io_read(KBC_STATUS_ADDR) & KBC_STATUS_BIT_OBF))
		goto kbc_exit;

	/* make状態でなければreturn */
	unsigned char keycode = io_read(KBC_DATA_ADDR);
	if (keycode & KBC_DATA_BIT_IS_BRAKE)
		goto kbc_exit;

	/* エコーバック処理 */
	char c = keymap[keycode];
	if (('a' <= c) && (c <= 'z'))
		c = c - 'a' + 'A';
	else if (c == '\n')
		putc('\r');
	putc(c);

kbc_exit:
	/* PICへ割り込み処理終了を通知(EOI) */
	set_pic_eoi(KBC_INTR_NO);
}

void kbc_init(void)
{
	set_intr_desc(KBC_INTR_NO, kbc_handler);
	enable_pic_intr(KBC_INTR_NO);
}
