#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
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
	/* get server host */
	char server_host[100];
	puts("input the host of server");
	cin >> server_host;
	hostent *host = gethostbyname(server_host);
	/* init server */
	server.sin_family = host->h_addrtype;
	server.sin_port = htons(SERVER_PORT);
	memcpy((char *) &server.sin_addr.s_addr, 
		host->h_addr_list[0], host->h_length);
	/* init client */
	client.sin_family = AF_INET;
	client.sin_port = htons(0);
	client.sin_addr.s_addr = htonl(INADDR_ANY);
	/* bind client */
	int ret = bind(sock, (struct sockaddr *) &client,
				(socklen_t)sizeof(client));
	if (ret < 0) {
		puts("bind error");
		exit(0);
	}
	/* send data */
	char msg[100];
	for (int i = 0; i < 10; i++) {
		gets(msg);
		ret = sendto(sock, msg, sizeof(msg), 0,
				(struct sockaddr *) &server, sizeof(server));
		if (ret < 0) {
			puts("send data error");
			continue;
		}
	}

	return 0;
}
