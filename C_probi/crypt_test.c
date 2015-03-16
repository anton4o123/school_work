#include <stdio.h>
#include <string.h>
#include <unistd.h>
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

void main() {
	char key[20];
	char salt[13] = "$6$I0F5LtVX$";
	char result[87];
	char expected[87];
	char set[27] = "abcdefghijklmnopqrstuvwxyz";
	long char_index;
//	static char *data[128];

//	scanf("%s", key);
//	scanf("%s", salt);

//	printf("%s\n", crypt(key, salt));

	strcat(expected, "$6$I0F5LtVX$vLRyhrfUf8NVT/ZLyZMKQmuTxMd18smssZ9cuQbjWM6Tuq7GVkeHC33Xgqo5PQfW8f65OtmPJtj1/zCMBZvcR.");
	scanf("%ld", &index_num);
	signal(SIGINT, int_handler);
	
	for(; keep_running; ++index_num) {
		char_index = index_num;
		result[0] = '\0';
		while(1) {
			strncat(result, &set[char_index % 26], 1);
	//		printf("%ld %ld\n", char_index, index_num);
			if(char_index < 26) {
				break;
			}
			char_index /= 26;
		}
		
		strrev(result);
		printf("%s\n", result);

		if(strcmp(crypt(result, salt), expected) == 0) {
			printf("%s\n", result);
			break;
		}
	}
}
