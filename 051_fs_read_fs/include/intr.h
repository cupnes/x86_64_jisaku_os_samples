#ifndef _INTR_H_
#define _INTR_H_

void set_intr_desc(unsigned char intr_no, void *handler);
void intr_init(void);

#endif
