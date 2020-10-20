#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	struct sockaddr_in sa;

	memset(&sa, '\0', sizeof(sa));
	int s = inet_pton(AF_INET, argv[1], &(sa.sin_addr)); // IPv4
	
	printf("inet_pton(AF_INET, \"%s\", in_addr*) -> %d\n", argv[1], s);
	printf("%d\n", sa.sin_addr.s_addr);

	char ipv4[INET_ADDRSTRLEN];
	s = inet_ntop(AF_INET, &(sa.sin_addr), ipv4, INET_ADDRSTRLEN);

	printf("inet_ntop(AF_INET, in_addr*, char*, INET_ADDRSTRLEN) -> %d\n", s);
	printf("%s\n", ipv4);
}
