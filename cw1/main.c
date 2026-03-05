#include <stdio.h>
#include <stdint.h>

int simple_math(int a) {
    return a * 2;
}

int simple_math_2(int a) {
    return a * 16;
}

uint8_t get_first_byte(uint32_t n) {
    // Rzutujemy wskaźnik na int32 na wskaźnik na uint8 (bajt)
    uint8_t* p = (uint8_t*)&n;
    return *p;
}

int main() {
    int in = 0x11223344;
    printf("%x\n",in);
    printf("%x",get_first_byte(in));

    int a = 2147483647; 
    printf("%x\n",a);
    printf("%d\n",a);

    a = a + 1;
    printf("%x\n",a);
    printf("%d\n",a);

    return 0;
} 

