#include <iv.h>
#include <fb.h>
#include <fs.h>
#include <common.h>

struct file *iv_files[MAX_IV_FILES];
unsigned long long iv_num_files;
unsigned long long iv_idx = 0;

void view(struct file *f)
{
	memcpy(fb.base, f->data, f->size);
}

void view_idx(unsigned long long idx)
{
	view(iv_files[idx]);
}

void iv_init(void)
{
	iv_num_files = get_files(iv_files);
	view_idx(iv_idx);
}

void iv_kbc_handler(char c)
{
	switch (c) {
	case 'j':
		if (iv_idx < iv_num_files - 1)
			view_idx(++iv_idx);
		break;
	case 'k':
		if (iv_idx > 0)
			view_idx (--iv_idx);
	}
}
