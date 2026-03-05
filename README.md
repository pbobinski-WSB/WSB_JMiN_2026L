# WSB-JMiN-2026L

```text
./docker
  ├── Dockerfile
  ├── docker-compose.yml
```

## 1. Uruchamianie środowiska

**Opcja A (W katalogu z docker-compose.yml):**
```bash
docker compose up -d
docker compose exec lab bash
```

**Opcja B (Z dowolnego katalogu - wymaga zbudowania obrazu wcześniej):**
```bash
# Linux/Mac/PowerShell
docker run --rm -it -v ${PWD}:/lab --cap-add=SYS_PTRACE --security-opt seccomp=unconfined lowlevel-env bash
```

```ps
function lab { docker run --rm -it -v ${PWD}:/lab --cap-add=SYS_PTRACE --security-opt seccomp=unconfined lowlevel-env bash }
```

## 2. Kompilacja (GCC)
Zamiana kodu C na plik wykonywalny (ELF).

*   **Zwykła kompilacja:**
    `gcc main.c -o main`
