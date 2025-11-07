build:
	cmake -S . -B build
	cmake --build build
# install the python package
build-container:
	docker build . -f Containerfile -t phys
	docker container rm phys-builder
	docker create --name phys-builder --rm phys
	docker cp phys-builder:/app/dist/ .
	docker cp phys-builder:/app/wheelhouse/ dist/
# install the python package
install:
	pip install . --no-deps --force-reinstall -v
# generate python stubs
stubs:
	pybind11-stubgen --output python phys
# package as wheel
wheel:
	python -m build --wheel
# run c++ core unit tests
test-cpp:
	cd build/tests && ctest --output-on-failure
# run python problem set tests
test-python:
	python -m pytest -v
# run formatting tasks
format:
	find src -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i
	ruff format src
# run linting tasks
lint:
	run-clang-tidy -p build -header-filter=".*/inc/.*" -exclude-header=".*extern.*" python src tests
	ruff check python --exclude "*.pyi"
# clean the cached directory
clean:
	cmake --build build --target clean
	ruff clean
# clean the cached directory
clean-full:
	rm -rf build/
# run all tests
test: test-cpp test-python
# run all ci actions
ci: build format lint test
