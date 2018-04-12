#ifndef _FS_H_
#define _FS_H_

#define FILE_NAME_LEN	28

struct file {
	char name[FILE_NAME_LEN];
	unsigned int size;
	unsigned char data[0];
};

void fs_init(void *_fs_start);
struct file *open(char *name);
unsigned long long get_files(struct file *files[]);

#endif
