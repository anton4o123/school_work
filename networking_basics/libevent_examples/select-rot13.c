#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

#define MAX_LINE 16384

char rot13_char(char c) {
	if((c>='a' && c<='m') || (c>='A' && c<='M')) {
		return c+13;
	} else if((c>='n' && c<='z') || (c>='N' && c<='Z')) {
		return c-13;
	} else {
		return c;
	}
}

struct fd_state {
	char buffer[MAX_LINE];
	ssize_t buffer_used;

	int writing;
	ssize_t n_written;
	ssize_t write_upto;
};

struct fd_state* alloc_fd_state() {
	struct fd_state *state=malloc(sizeof(struct fd_state));
	if(!state) {
		return 0;
	}
	state->buffer_used=state->writing=state->n_written=state->write_upto=0;
	return state;
}

void free_fd_state(struct fd_state *state) {
	free(state);
}

void make_nonblocking(int fd) {
	fcntl(fd, F_SETFL, O_NONBLOCK);
}

int do_read(int fd, struct fd_state *state) {
	char buf[1024];
	int i;
	ssize_t result;

	while(1) {
		if( (result=recv(fd, buf, sizeof(buf), 0))<=0) {
			break;
		}

		for(i=0;i<result;++i) {
			if(state->buffer_used<sizeof(state->buffer)) {
				state->buffer[state->buffer_used]=rot13_char(buf[i]);
			}
			if(buf[i]=='\n') {
				state->writing=1;
				state->write_upto=state->buffer_used;
			}
		}
	}

	if(result==0) {
		return 1;
	} else if(result<0) {
		if(errno==EAGAIN) {
			return 0;
		}
		return -1;
	}
	return 0;
}

int do_write(int fd, struct fd_state *state) {
	while(state->n_written<state->write_upto) {
		ssize_t result=send(fd, state->buffer+state->n_written, state->write_upto-state->n_written,0);
		if(result<0) {
			if(errno==EAGAIN) {
				return 0;
			}
			return -1;
		}
		assert(result!=0);
		state->n_written+=result;
	}

	if(state->n_written==state->buffer_used) {
		state->n_written=state->write_upto=state->buffer_used=0;
	}
	state->writing=0;
	return 0;
}

void run() {
	int listener;
	struct fd_state *state[FD_SETSIZE];
	struct sockaddr_in sin;
	int i, maxfd;
	fd_set readset, writeset, exset;

	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=0;
	sin.sin_port=htons(40713);

	for(i=0;i<FD_SETSIZE;++i) {
		state[i]=NULL;
	}

	if( (listener=socket(AF_INET, SOCK_STREAM, 0))<0) {
		perror("socket");
		exit(-1);
	}
	make_nonblocking(listener);
#ifndef WIN32
	{
		int one=1;
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
	}
#endif

	if(bind(listener, (struct sockaddr*)&sin, sizeof(sin))<0) {
		perror("bind");
		exit(-1);
	}

	if(listen(listener, 16)<0) {
		perror("listen");
		exit(-1);
	}

	FD_ZERO(&readset);
	FD_ZERO(&writeset);
	FD_ZERO(&exset);

	FD_SET(listener, &readset);

	for(i=0;i<FD_SETSIZE;++i) {
		if(state[i]){
			if(i>maxfd) {
				maxfd=i;
			}
			FD_SET(i, &readset);
			if(state[i]->writing) {
				FD_SET(i, &writeset);
			}
		}
	}

	if(select(maxfd, &readset, &writeset, &exset, NULL)<0) {
		perror("select");
		exit(-1);
	}

	if(FD_ISSET(listener, &readset)) {
		struct sockaddr_storage ss;
		socklen_t slen=sizeof(ss);

		int fd=accept(listener, (struct sockaddr*)&ss, &slen);
		if(fd<0) {
			perror("accept");
		} else if(fd>FD_SETSIZE) {
			close(fd);
		} else {
			make_nonblocking(fd);
			state[fd]=alloc_fd_state();
			assert(state[fd]);
		}
	}

	for(i=0;i<maxfd+1;++i) {
		int r=0;
		if(i==listener) {
			continue;
		}

		if(FD_ISSET(i, &readset)) {
			r=do_read(i, state[i]);
		}
		if(r==0 && FD_ISSET(i, &writeset)) {
			r=do_write(i, state[i]);
		}
		if(r) {
			free_fd_state(state[i]);
			state[i]=NULL;
			close(i);
		}
	}
}

int main(int argc, char const *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);

	run();
	return 0;
}