#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#define SERVER_PORT 1086

int main() {
	struct sockaddr_in server, client;
	/* create socket */
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		puts("create socket error");
		exit(1);
	}

	/* bind local server */
	server.sin_family = AF_INET;
	// refer to unsure address
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(SERVER_PORT);
	int ret = 0;
	ret = bind(sock, (struct sockaddr *) &server, sizeof(server));
	if (ret < 0) {
		puts("bind server error");
		exit(1);
	}
	puts("waiting for data from client");

	/* received message */
	char msg[100];
	int client_len;
	while(1) {
		memset(msg, 0x0, sizeof(msg));
		client_len = sizeof(client);
		ret = recvfrom(sock, msg, 100, 0, 
				(struct sockaddr *) &client, 
				(socklen_t *) &client_len);
		if (ret < 0) {
			puts("received message error");
			continue;
		}
		printf("received from %s and port: %u : messagee :%s\n",
			inet_ntoa(client.sin_addr), ntohs(client.sin_port),
			msg);
	}
	return 0;
}
