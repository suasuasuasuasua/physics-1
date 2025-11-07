FROM quay.io/pypa/manylinux_2_28_aarch64

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
