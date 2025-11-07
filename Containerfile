# Build argument to specify manylinux platform architecture
# Supports: x86_64 (default), aarch64
# Usage:
#   docker build --build-arg PLATFORM_ARCH=x86_64 -f Containerfile -t phys .
#   docker build --build-arg PLATFORM_ARCH=aarch64 -f Containerfile -t phys .
ARG PLATFORM_ARCH=x86_64

FROM quay.io/pypa/manylinux_2_28_${PLATFORM_ARCH}

WORKDIR /app

RUN dnf update -y && dnf install -y \
	cmake \
	git \
	make \
	ninja-build \
	python3.12 \
	python3.12-devel
COPY pyproject.toml ./
RUN --mount=type=cache,target=/root/.cache python3.12 -m venv venv \
	&& . venv/bin/activate \
	&& pip install -U pip \
	&& pip install build auditwheel pytest wheel

COPY extern extern
COPY CMakeLists.txt Makefile README.md ./
COPY tests tests
COPY inc inc
COPY src src
COPY python python

RUN . venv/bin/activate \
	&& make install test wheel \
	&& python -m auditwheel repair dist/*.whl
