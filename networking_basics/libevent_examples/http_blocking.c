#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char const *argv[])
{
	const char query[]=
		"GET / HTTP/1.0\r\n"
		"Host: www.google.com\r\n"
		"\r\n";
	const char hostname[]="www.google.com";
	struct sockaddr_in sin;
	struct hostent *h;
	const char *cp;
	int fd;
	ssize_t n_written, remaining;
	char buf[1024];

	h=gethostbyname(hostname);
	if(!h) {
		fprintf(stderr, "Couldn't lookup %s: %s\n", hostname, hstrerror(h_errno));
		return 1;
	}

	if(h->h_addrtype!=AF_INET) {
		fprintf(stderr, "No ipv4 support, sorry!\n");
		return 1;
	}

	if( (fd=socket(AF_INET, SOCK_STREAM, 0))<0) {
		perror("socket error");
		return 1;
	}

	sin.sin_family=AF_INET;
	sin.sin_port=htons(80);
	sin.sin_addr=*(struct in_addr*)h->h_addr;
	if(connect(fd, (struct sockaddr*)&sin, sizeof(sin))<0) {
		perror("connect error");
		close(fd);
		return 1;
	}

	cp=query;
	remaining=strlen(query);

	while(remaining) {
		if( (n_written=send(fd, cp, remaining, 0))<=0) {
			perror("send");
			return 1;
		}
		remaining-=n_written;
		cp+=n_written;
	}

	while(1) {
		ssize_t result=recv(fd, buf, sizeof(buf), 0);
		if(result<0) {
			perror("recv");
			close(fd);
			return 1;
		} else if(result==0) {
			break;
		}
		fwrite(buf, 1, result, stdout);
	}

	close(fd);
	return 0;
}