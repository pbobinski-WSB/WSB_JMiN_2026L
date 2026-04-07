const PASSWORD_PTR = 0;  // Zaczynamy od adresu 0 (miejsce na 10 bajtów)
const ADMIN_PTR = 10;    // Zaraz za hasłem (pod adresem 10) leży flaga admina

export function init(): void {
  // Domyślnie nikt nie jest adminem
  store<u8>(ADMIN_PTR, 0); 
}

export function checkAdmin(): i32 {
  // Zwraca wartość flagi z adresu 10
  return load<u8>(ADMIN_PTR); 
}

// Podatna funkcja!
// Programista kopiuje znaki hasła do pamięci, ale zapomniał sprawdzić 
// czy passwordLength nie jest większe niż nasze przydzielone 10 bajtów!
export function login(passwordLength: i32, secretByte: u8): void {
  for (let i = 0; i < passwordLength; i++) {
    store<u8>(PASSWORD_PTR + i, secretByte); 
  }
}