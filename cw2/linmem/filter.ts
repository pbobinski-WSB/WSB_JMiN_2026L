// filter.ts
export function invertColors(width: i32, height: i32): void {
  // Obliczamy ile mamy pikseli
  let numPixels = width * height;
  
  for (let i = 0; i < numPixels; i++) {
    // Każdy piksel zajmuje 4 bajty w pamięci: Red, Green, Blue, Alpha
    // ptr to nasz WSKAŹNIK (pointer) na konkretny bajt
    let ptr = i * 4; 
    
    // Odczytujemy aktualny kolor (0-255), odwracamy go (255 - x) i zapisujemy z powrotem
    store<u8>(ptr,     255 - load<u8>(ptr));     // R (Czerwony)
    store<u8>(ptr + 1, 255 - load<u8>(ptr + 1)); // G (Zielony)
    store<u8>(ptr + 2, 255 - load<u8>(ptr + 2)); // B (Niebieski)
    
    // ptr + 3 to kanał Alpha (przezroczystość) - nie modyfikujemy go, żeby obrazek nie zniknął
  }
}