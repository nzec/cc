#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

int errno;

int main(int argc, char *argv[]) {
	int status;
	struct addrinfo hints, *res, *p;

	if (argc != 2) {
		fprintf(stderr, "Usage: ./showip [hostname]\n");
		return 1;
	}

	// Initialize everything to 0
	memset(&hints, 0, sizeof hints);

	// Return Socket belonging to any Family
	hints.ai_family = AF_UNSPEC;
	// Use Stream Sockets
	hints.ai_socktype = SOCK_STREAM;
	// Works with any Porotocl
	hints.ai_protocol = 0;

	if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}
	
	char *ipstr[INET6_ADDRSTRLEN];

	// Loop through the linked list whose first element is res
	for (p = res; p != NULL; p = p->ai_next) {
		struct sockaddr_in *sin = (struct sockaddr_in *)(p->ai_addr);

		if ((status = inet_ntop(p->ai_family, &(sin->sin_addr), ipstr, sizeof ipstr)) == NULL) {
			perror("inet_ntop: ");
			return 3;
		}

		// Couldn't find an automated way to do this
		char *family = (p->ai_family == AF_INET ? "IPv4" : "IPv6");
		printf("%s: %s\n", family, ipstr);
	}
}
