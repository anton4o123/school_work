#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 4096
#define LISTENQ 1024

void main() {
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;
	
	if( (listenfd=socket(AF_INET, SOCK_STREAM, 0))<0) {
		perror("socket error");
		exit(-1);
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(13);
	
	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0) {
		perror("bind error");
		exit(-1);
	}
	
	if(listen(listenfd, LISTENQ)<0) {
		perror("listen error");
		exit(-1);
	}
	
	for(;;) {
		if( (connfd=accept(listenfd, (struct sockaddr*)NULL , NULL))<0) {
			perror("accept error");
			exit(-1);
		}
		
		ticks=time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		if(write(connfd, buff, strlen(buff))<0) {
			perror("write error");
			exit(-1);
		}
		if(close(connfd)<0) {
			perror("close error");
			exit(-1);
		}
	}
}
