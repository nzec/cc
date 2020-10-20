// C program to illustrate
// read system Call
#include<stdio.h>
#include <fcntl.h>
int main() {
	int fd, sz;
	char c[100];

	fd = open("foo.txt", O_RDONLY);

	if (fd < 0) {
		perror("r1");
		exit(1);
	}

	int zz = 10;
	sz = read(fd, c, zz);
	printf("read(%d, c, %d) -> %d\n", fd, zz, sz);
	c[sz] = '\0';
	printf("%s", c);
}

