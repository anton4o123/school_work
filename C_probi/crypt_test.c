#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <crypt.h>
#include <signal.h>

static int keep_running = 1;
long index_num;

void int_handler(int dummy) {
	keep_running = 0;
	printf("%ld\n", index_num);
}

void strrev(char *p) {
	char *q = p;
	while(q && *q) ++q;
	for(--q; p < q; ++p, --q)
		*p = *p ^ *q,
		*q = *p ^ *q,
		*p = *p ^ *q;
}

void test_combination_by_fixed_length(char *expected, char *salt, char *set, int number_of_symbols) {
	long char_index;
	char result[99];
	long top_boundary = (long)pow((double)strlen(set), (double)number_of_symbols);
	
	for(; keep_running && index_num < top_boundary; ++index_num) {
		char_index = index_num;
		result[0] = '\0';
		while(1) {
			strncat(result, &set[char_index % 26], 1);
			if(char_index < 26) {
				break;
			}
			char_index /= 26;
		}

		strrev(result);
		printf("%s\n", result);

		if(strcmp(crypt(result, salt), expected) == 0) {
			printf("%s\n", result);
			exit(0);
		}
	}
}

void main() {
	char key[20];
	char salt[13] = "$6$I0F5LtVX$";
	char result[87];
	char expected[99] = "\0";
	char set[27] = "abcdefghijklmnopqrstuvwxyz";
	long char_index;
//	static char *data[128];

//	scanf("%s", key);
//	scanf("%s", salt);

//	printf("%s\n", crypt(key, salt));

	strcat(expected, "$6$I0F5LtVX$GvWOOHQS2mlaMtxVyNeLL1ELRm7w8xWo0bwEcKvigRqpWxUH2enq3kW1HSkTvmNlj6.6KxKUgoIO5o2jft2OG/");
	scanf("%ld", &index_num);
	signal(SIGINT, int_handler);
	
	test_combination_by_fixed_length(expected, salt, set, 2);
}
