#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int *table;
int flour=1000;
pthread_mutex_t kitchen;

void *mother() {
	int sec=0,i=0;
	
	while(flour>0) {
		if(table[i]==0) {
			pthread_mutex_lock(&kitchen);
			sec=rand()/(RAND_MAX/100)+1;
			if(sec>flour) {
				sec=flour;
			}
			usleep(sec*1000);
			flour-=sec;
			table[i]=1;
			printf("Pasta gotova: %d!\n", i);
			i++;
			if(i>=4) {
				i=0;
			}
			pthread_mutex_unlock(&kitchen);
		}
	}
	pthread_exit(NULL);
}

void *ivancho() {
	int sec=0,i=0;

	while(flour>0 || table[i]==1) {
		if(table[i]==1) {
			pthread_mutex_lock(&kitchen);
			sec=rand()/(RAND_MAX/100)+1;
			usleep(sec*1000);
			table[i]=0;
			printf("Pasta izqdena: %d!\n", i);
			i++;
			if(i>=4) {
				i=0;
			}
			pthread_mutex_unlock(&kitchen);
		}
	}
	pthread_exit(NULL);
}

void main() {
	int i;
	table=malloc(4*sizeof(int));
	for(i=0;i<4;++i) {
		table[i]=0;
	}
	pthread_t maika, ivan;
	
	pthread_mutex_init(&kitchen, NULL);
	
	pthread_create(&maika, NULL, mother, NULL);
	pthread_create(&ivan, NULL, ivancho, NULL);
	
	pthread_join(maika, NULL);
	pthread_join(ivan, NULL);
	
	printf("Brashno: %d\n", flour);
	
	pthread_mutex_destroy(&kitchen);
	free(table);
}
