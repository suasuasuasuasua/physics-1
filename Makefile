build:
	cmake -S . -B build
	cmake --build build
# build with coverage enabled
build-coverage:
	cmake -S . -B build -DCODE_COVERAGE=ON
	cmake --build build
# install the python package
install:
	pip install . --no-deps --force-reinstall
# generate python stubs
stubs:
	python -m pybind11-stubgen --output src physics_1
# package as wheel
wheel:
	python -m build --wheel
# run all tests
test: test-cpp test-python
# run all tests with coverage (requires build-coverage to be run first for C++ coverage)
test-coverage: test-cpp test-python-coverage coverage-report
# generate C++ coverage report from collected gcov data
coverage-report:
	gcovr --root . --filter src/ --filter inc/ --exclude 'extern/*' --xml -o coverage-cpp.xml --print-summary
# run c++ core unit tests
test-cpp:
	cd build && ctest --output-on-failure
# run python problem set tests
test-python:
	python -m pytest -v
# run python tests with coverage
test-python-coverage:
	python -m pytest -v --cov=physics_1 --cov-report=xml --cov-report=term
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
