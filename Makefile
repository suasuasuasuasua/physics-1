build:
	cmake -S . -B build
	cmake --build build
# install the python package
install:
	pip install . --no-deps --force-reinstall -v
# generate python stubs
stubs:
	pybind11-stubgen --output python physics_1
# package as wheel
wheel:
	python -m build --wheel
# run all tests
test: test-cpp test-python
# run c++ core unit tests
test-cpp:
	cd build && ctest --output-on-failure
# run python problem set tests
test-python:
	python -m pytest -v
# run formatting tasks
format:
	find src -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i
	ruff format src
# run linting tasks
lint:
	run-clang-tidy src -p build -header-filter ".*inc.*"
	ruff check src
# clean the cached directory
clean:
	cmake --build build --target clean
	ruff clean
# clean the cached directory
clean-full:
	rm -rf build/
