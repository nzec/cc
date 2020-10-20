#include <stdio.h>
#include <arpa/inet.h>

int main() {
	long a;
	scanf("%ld", &a);
	printf("%d\n", htonl(a));
	printf("%d\n", ntohl(a));
}
