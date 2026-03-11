#include <stdio.h>

void vulnerable_function() {
    char buffer[64];
    printf("Wprowadz tajne haslo: \n");
    gets(buffer); // BŁĄD KRYTYCZNY: gets() nie sprawdza długości!
}

int main() {
    vulnerable_function();
    printf("Autoryzacja odrzucona.\n");
    return 0;
}
