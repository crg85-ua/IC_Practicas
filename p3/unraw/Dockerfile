FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive
ARG TZ=Europe/Madrid

RUN apt update && \
    apt upgrade -y && \
    apt install -y \
    time \
    gcc \
    g++ \
    make \
    cmake \
    libopencv-dev \
    libopenmpi-dev
