const PASSWORD_PTR = 0;   // Wewnętrzny bufor programu (10 bajtów)
const ADMIN_PTR = 10;     // Tuż za buforem leży nasza flaga
const INPUT_BUFFER = 100; // Skrzynka podawcza dla JavaScriptu

export function init(): void {
  store<u8>(ADMIN_PTR, 0); // Domyślnie brak uprawnień
}

export function checkAdmin(): i32 {
  return load<u8>(ADMIN_PTR); 
}

// BŁĄD KRYTYCZNY: Kopiujemy dane ze "skrzynki podawczej" do wewnętrznego bufora,
// ale nie sprawdzamy, czy inputLength mieści się w naszych 10 bajtach!
export function login(inputLength: i32): void {
  for (let i = 0; i < inputLength; i++) {
    // Odczytaj bajt ze strefy wejściowej (od adresu 100)
    let char = load<u8>(INPUT_BUFFER + i);
    
    // Zapisz do bufora wewnętrznego (od adresu 0).
    // Jeśli i >= 10, nadpiszemy ADMIN_PTR!
    store<u8>(PASSWORD_PTR + i, char); 
  }
}