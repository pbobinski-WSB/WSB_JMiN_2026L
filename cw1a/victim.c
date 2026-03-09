#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Funkcja, której normalnie nikt nie wywołuje.
// Cel: zmusić program, żeby tu skoczył.
void secret_backdoor() {
    printf("!!! HACKED !!! Zyskałeś dostęp do powłoki administratora.\n");
    // W prawdziwym ataku tu byłoby: system("/bin/sh");
    exit(0);
}

void vulnerable_function() {
    char buffer[64]; // Miejsca jest tylko na 64 znaki
    
    printf("Podaj hasło: ");
    // BŁĄD: gets() nie sprawdza długości! Wczyta tyle, ile podasz.
    gets(buffer); 
}

int main() {
    vulnerable_function();
    printf("Nie udało się zgadnąć hasła.\n");
    return 0;
}