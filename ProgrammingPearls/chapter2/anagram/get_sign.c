#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LEN 100

int main() {
    char word[MAX_LEN];
    int numcnt[26];
    while(scanf("%s", word) != EOF) {
        memset(numcnt, 0, sizeof(numcnt));
        int len = (int)strlen(word);
	for (int i = 0; i < len; i++) {
	    numcnt[word[i] - 'a']++;
	}
	printf("%s  ", word);
	for (int i = 0; i < 26; i++) {
	    if (numcnt[i] > 0) {
	        printf("%c", (char)(i+'a'));
		if (numcnt[i] > 1) {
		    printf("%d", numcnt[i]);
		}
	    }
	}
	printf("\n");
    }
    return 0;
}
