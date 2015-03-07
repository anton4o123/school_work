#include "../lib/unp.h"
#include "../lib/wrapsock.c"
#include "../lib/wrapstdio.c"
#include "../lib/wraplib.c"
#include "../lib/str_cli.c"
#include "../lib/writen.c"
#include "../lib/readline.c"

int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in servaddr;
	
	if(argc!=2) {
		err_quit("usage: cli <IPAddress>");
	}
	
	sockfd=Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
	str_cli(stdin, sockfd);
	
	exit(0);
}
