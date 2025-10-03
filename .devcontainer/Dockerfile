FROM debian:bookworm-slim AS downloader

# install basic tools
RUN apt-get update \
    && apt-get -y install --no-install-recommends apt-utils \
    && apt-get install -y \
    curl \
    xz-utils \
    unzip \
    wget

RUN mkdir -p /tmp/dc-downloads /tmp/dc-extracted

ARG GCC_VERSION=13.3.rel1
ARG GCC_URI=https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/$GCC_VERSION/binrel/arm-gnu-toolchain-$GCC_VERSION-x86_64-arm-none-eabi.tar.xz
RUN mkdir -p /tmp/dc-downloads /tmp/dc-extracted/gcc \
    && curl -o /tmp/dc-downloads/gcc-arm.tar.xz  $GCC_URI \
    && xz -d /tmp/dc-downloads/gcc-arm.tar.xz \
    && tar -xvf /tmp/dc-downloads/gcc-arm.tar -C /tmp/dc-extracted/gcc --strip-components 1 \
    && rm -rf /tmp/dc-extracted/gcc/share/doc/ /tmp/dc-extracted/gcc/share/gcc-arm-none-eabi/samples/

ARG CMAKE_VERSION=3.31.6
ARG CMAKE_SCRIPT=https://github.com/Kitware/CMake/releases/download/v$CMAKE_VERSION/cmake-$CMAKE_VERSION-linux-x86_64.sh
RUN wget $CMAKE_SCRIPT \
    -q -O /tmp/dc-downloads/cmake-install.sh \
    && chmod u+x /tmp/dc-downloads/cmake-install.sh \
    && mkdir -p /tmp/dc-extracted/cmake \
    && /tmp/dc-downloads/cmake-install.sh --skip-license --prefix=/tmp/dc-extracted/cmake \
    && rm /tmp/dc-downloads/cmake-install.sh

# nf interpreter:
ARG SVD_FILE=https://raw.githubusercontent.com/cmsis-svd/cmsis-svd-data/main/data/NXP/MIMXRT1062.svd
RUN curl -o /tmp/dc-downloads/MIMXRT1062.svd $SVD_FILE


FROM debian:bookworm AS devcontainer

# Avoid warnings by switching to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# Configure apt and install packages
RUN apt-get update \
    && apt-get -y install --no-install-recommends apt-utils dialog icu-devtools 2>&1 \
    && apt-get install --reinstall -y \
    git \
    curl \
    ninja-build \
    srecord \
    libncurses5 \
    gcovr   \
    gdb \
    build-essential \
    python3 \
    clang-format-19 \
    texinfo \
    doxygen \
    docbook-utils \
    latex-mk \
    latex-make \
    texlive-font-utils \
    graphviz \
    libc6-dbg \
    wget \
    ca-certificates

RUN update-ca-certificates

# Create needed directories
RUN mkdir -p /usr/local/bin/gcc

# install valgrind
RUN wget --no-check-certificate https://sourceware.org/pub/valgrind/valgrind-3.20.0.tar.bz2 && tar -xaf valgrind-3.20.0.tar.bz2 && (cd valgrind-3.20.0 && ./configure  --prefix=/usr && make -j && make install) && rm -fr valgrind-3.20.0*

ENV PATH=/usr/local/bin/gcc/bin:$PATH
ENV ARM_GCC_PATH=/usr/local/bin/gcc/bin

# Copy from our other container
COPY --from=downloader /tmp/dc-extracted/gcc /usr/local/bin/gcc
COPY --from=downloader /tmp/dc-extracted/cmake /usr

# Clean up downloaded files
RUN apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=dialog
RUN mkdir -p /workspaces
WORKDIR /workspaces

