#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>

#define SERV_PORT 9877
#define LISTENQ 1024
#define MAXLINE 4096

int main(int argc, char const *argv[])
{
	int i, maxi, maxfd, listenfd, connfd, sockfd;
	int nready, client[FD_SETSIZE];
	ssize_t n;
	fd_set rset, allset;
	char buf[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	if( (listenfd=socket(AF_INET, SOCK_STREAM, 0))<0) {
		perror("socket error");
		exit(-1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(SERV_PORT);

	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0) {
		perror("bind error");
		exit(-1);
	}

	if(listen(listenfd, LISTENQ)<0) {
		perror("listen error");
		exit(-1);
	}

	maxfd=listenfd;
	maxi=-1;
	for(i=0;i<FD_SETSIZE;client[i]=-1);
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	for(;;) {
		rset=allset;
		if( (nready=select(maxfd+1, &rset, NULL, NULL, NULL))<0) {
			perror("select error");
			exit(-1);
		}

		if(FD_ISSET(listenfd, &rset)) {
			clilen=sizeof(cliaddr);
			if( (connfd=accept(listenfd, (struct sockaddr*)&cliaddr, &clilen))<0) {
				perror("accept error");
				exit(-1);
			}

			for(i=0;i<FD_SETSIZE;++i) {
				if(client[i]<0) {
					client[i]=connfd;
					break;
				}
			}

			if(i==FD_SETSIZE) {
				printf("too many clients\n");
				exit(-1);
			}
			FD_SET(connfd, &allset);
			if(connfd>maxfd) {
				maxfd=connfd;
			}
			if(i>maxi) {
				maxi=i;
			}
			if(--nready<=0) {
				continue;
			}
		}

		for(i=0;i<=maxi;++i) {
			if( (sockfd=client[i])<0) {
				continue;
			}

			if(FD_ISSET(sockfd, &rset)) {
				if( (n=read(sockfd, buf, MAXLINE))==0) {
					if(close(sockfd)<0) {
						perror("close error");
						exit(-1);
					}
					FD_CLR(sockfd, &allset);
					client[i]=-1;
				} else if(n<0) {
					perror("read error");
					exit(-1);
				} else {
					if(write(sockfd, buf, n)<0) {
						perror("write error");
						exit(-1);
					}
				}

				if(--nready<=0) {
					break;
				}
			}
		}
	}

	return 0;
}