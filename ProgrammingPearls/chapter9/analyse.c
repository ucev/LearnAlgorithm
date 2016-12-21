#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main() {
    int n = 100234324512;
    time_t s0 = clock();
    for (int i = 0; i < 10000000; i++)
        n % 13;
    time_t s1 = clock();
    printf("%% %ld\n", s1 - s0);
    for (int i = 0; i < 10000000; i++) {
        n - 13;
    }
    time_t s2 = clock();
    printf("/ %ld\n", s2 - s1);
    return 0;
}
