FROM ubuntu:22.04 as build

RUN apt-get update && \
    apt-get install -y \
        binutils-mips-linux-gnu \
        bsdextrautils \
        build-essential \
        git \
        libsdl2-dev \
        pkgconf \
        python3

RUN mkdir /sm64ex-alo
WORKDIR /sm64ex-alo
ENV PATH="/sm64ex-alo/tools:${PATH}"

CMD echo 'Usage: docker run --rm -v ${PWD}:/sm64ex-alo sm64ex-alo make VERSION=us -j4\n' \
         'See https://github.com/AloUltraExt/sm64ex-alo/blob/master/README.md for more information'
