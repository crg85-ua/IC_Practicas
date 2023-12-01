#!/bin/bash
mkdir -p build
docker build -t unraw .
docker run -it --rm -v ".:/root/app" unraw sh -c "\
    cd /root/app && \
    cd build && \
    cmake .. && \
    make -j$(nproc) unraw && \
    cd .. && \
    time ./build/unraw _DSC2078.NEF _DSC2078.jpeg"
