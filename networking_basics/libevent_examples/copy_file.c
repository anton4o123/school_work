#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#define MAX_LINE 16384

void do_read(evutil_socket_t fd, short events, void *arg);
void do_write(evutil_socket_t fd, short events, void *arg);

void readcb(struct bufferevent *bev, void *ctx) {
	struct evbuffer *input, *output;
	char *line;
	size_t n, file_bytes;
	int i;

	input=bufferevent_get_input(bev);
	output=bufferevent_get_output(bev);

	while( (line=evbuffer_readln(input, &n, EVBUFFER_EOL_LF))) {
		line[strlen(line)-1]='\0';
		int fd=open(line, O_RDONLY);
		if(fd<0) {
			perror("open");
			return;
		}
		char file_buf[1024];

		while( (file_bytes=read(fd, file_buf, 1024))) {
			evbuffer_add(output, file_buf, file_bytes);
		}
		evbuffer_add(output, "\n", 1);
		free(line);
	}

	if(evbuffer_get_length(input)>=MAX_LINE) {
		char buf[1024];

		while(evbuffer_get_length(input)) {
			int n=evbuffer_remove(input, buf, sizeof(buf));
			evbuffer_add(output, buf, n);
		}
		evbuffer_add(output, "\n", 1);
	}
}

void errorcb(struct bufferevent *bev, short error, void *cbx) {
	bufferevent_free(bev);
}

void do_accept(evutil_socket_t listener, short event, void *arg) {
	struct event_base *base=arg;
	struct sockaddr_storage ss;
	socklen_t slen=sizeof(ss);

	int fd=accept(listener, (struct sockaddr*)&ss, &slen);
	if(fd<0) {
		perror("accept");
	} else if(fd>FD_SETSIZE) {
		close(fd);
	} else {
		struct bufferevent *bev;
		evutil_make_socket_nonblocking(fd);
		bev=bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
		bufferevent_setcb(bev, readcb, NULL, errorcb, NULL);
		bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
		bufferevent_enable(bev, EV_READ | EV_WRITE);
	}
}

void run() {
	evutil_socket_t listener;
	struct sockaddr_in sin;
	struct event_base *base;
	struct event *listener_event;

	base=event_base_new();
	if(!base) {
		return;
	}

	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=0;
	sin.sin_port=htons(40713);

	listener=socket(AF_INET, SOCK_STREAM, 0);
	evutil_make_socket_nonblocking(listener);

#ifndef WIN32
	{
		int one=1;
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
	}
#endif

	if(bind(listener, (struct sockaddr*)&sin, sizeof(sin))<0) {
		perror("bind");
		return;
	}

	if(listen(listener, 16)<0) {
		perror("listen");
		return;
	}

	listener_event=event_new(base, listener, EV_READ|EV_PERSIST, do_accept, (void*)base);
	event_add(listener_event, NULL);
	event_base_dispatch(base);	
}

int main(int argc, char const *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);

	run();
	return 0;
}