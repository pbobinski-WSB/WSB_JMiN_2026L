### "Smashing the Stack – Przejęcie kontroli nad procesem"

Nie wstrzykujemy własnego kodu (Shellcode), tylko wykorzystujemy istniejący kod wbrew intencjom programisty.

#### Krok A: Podatny Kod (victim.c)

#### Krok B: Kompilacja (Wyłączamy zabezpieczenia)

```bash
gcc -fno-stack-protector -no-pie -z execstack victim.c -o victim
```
*   `-fno-stack-protector`: Wyłącza "Kanarka" (Canary) – strażnika stosu.
*   `-no-pie`: Wyłącza losowość adresów kodu (adres funkcji `secret_backdoor` będzie stały).

### 3. Atak

#### Faza 1: Rekonesans (Gdzie jest cel?)
Pod jakim adresem w pamięci znajduje się funkcja `secret_backdoor`?

```bash
objdump -d victim | grep secret_backdoor
```
Wynik np.: `0000000000401146 <secret_backdoor>:`

#### Faza 2: Sabotaż (Gdzie jest punkt wejścia?)
W GD szukamy adresu powrotu, wstrzykując unikalny ciąg "śmieci"

1.  `gdb ./victim`
2.  `cyclic 100`.
3.  `run` -> Wklejamy powyższy.
4.  Program dostanie `SEGFAULT`, ale
5.  Patrzymy na rejestr `RIP` (Instruction Pointer) - będzie zawierał fragment wzorca (np. `0x6161616c` -> 'laaa'), trzeba znaleźć offset.

Np. tak:

W architekturze x86-64, w momencie wykonywania instrukcji `ret` (return), procesor pobiera adres powrotu ze szczytu stosu (tam, gdzie wskazuje `RSP`).

```text    
00:0000│ rsp 0x7fffffffe5b8 ◂— 'saaataaauaaavaaawaaaxaaayaaa'
```

```bash
cyclic -l saaa
```
*(Wystarczą pierwsze 4 znaki z tego, co leży pod `rsp`).*

Powinno zwrócić liczbę, prawdopodobnie **72**.


#### Faza 3: Exploit (Python)

```python
# Adres funkcji secret_backdoor (w Little Endian!)
# 0x0000000000401146 -> \x46\x11\x40\x00\x00\x00\x00\x00
```

Uruchomienie ataku:
```bash
python3 exploit.py | ./victim
```

---

### 4. Obrona (Low-Level Defense)


#### A. Stack Canary (Kanarek)
Kompilujemy bez flagi `-fno-stack-protector` (domyślnie włączone w GCC).

```bash
gcc -no-pie victim.c -o victim_protected
python3 exploit.py | ./victim_protected
```

