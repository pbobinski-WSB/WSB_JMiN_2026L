FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# 1. Instalujemy podstawowe narzędzia i WABT
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
    wabt \
    && rm -rf /var/lib/apt/lists/*

# 2. Instalujemy NOWEGO Node.js (v20) ze źródła NodeSource
RUN curl -fsSL https://deb.nodesource.com/setup_20.x | bash - && \
    apt-get install -y nodejs

# 3. Instalacja Pwndbg (bez zmian)
WORKDIR /root
RUN git clone https://github.com/pwndbg/pwndbg && \
    cd pwndbg && ./setup.sh

WORKDIR /lab
CMD ["/bin/bash"]