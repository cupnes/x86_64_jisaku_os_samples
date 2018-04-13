#include <common.h>

int strcmp(char *s1, char *s2)
{
	char is_equal = 1;

	for (; (*s1 != '\0') && (*s2 != '\0'); s1++, s2++) {
		if (*s1 != *s2) {
			is_equal = 0;
			break;
		}
	}

	if (is_equal) {
		if (*s1 != '\0') {
			return 1;
		} else if (*s2 != '\0') {
			return -1;
		} else {
			return 0;
		}
	} else {
		return (int)(*s1 - *s2);
	}
}

void memcpy(void *dst, void *src, unsigned long long size)
{
	unsigned char *d = (unsigned char *)dst;
	unsigned char *s = (unsigned char *)src;
	for (; size > 0; size--)
		*d++ = *s++;
}
