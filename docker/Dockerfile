FROM ubuntu:22.04

# Unikamy pytań o strefę czasową podczas instalacji
ENV DEBIAN_FRONTEND=noninteractive

# Instalacja narzędzi podstawowych
RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    git \
    vim \
    nano \
    python3 \
    python3-pip \
    wget \
    curl \
    file \
    bsdmainutils \
    && rm -rf /var/lib/apt/lists/*

# Instalacja Pwndbg (nakładka na GDB - standard w CTF)
# Ułatwia czytanie rejestrów i stosu
WORKDIR /root
RUN git clone https://github.com/pwndbg/pwndbg && \
    cd pwndbg && \
    ./setup.sh

# Ustawienie katalogu roboczego
WORKDIR /lab

CMD ["/bin/bash"]