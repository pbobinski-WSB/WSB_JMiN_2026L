#include <stdio.h>
int main() {
    long long sum = 0;
    // Miliard iteracji
    for(long long i = 0; i < 1000000000; i++) {
        sum += i;
    }
    printf("%lld\n", sum);
    return 0;
}