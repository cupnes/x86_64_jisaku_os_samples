#ifndef _IV_H_
#define _IV_H_

#include <fs.h>

#define MAX_IV_FILES	100

void view(struct file *f);
void view_idx(unsigned long long idx);
void iv_init(void);
void iv_kbc_handler(char c);

#endif
