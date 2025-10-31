build:
	cmake -S . -B build
	cmake --build build
# install the python package
install:
	pip install .
# package as wheel
wheel:
	python -m build --wheel
# run unit tests
test:
	python -m pytest -v
# run formatting tasks
format:
	find src -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i
	ruff format src
# run linting tasks
lint:
	run-clang-tidy src -p build
	ruff check src
# clean the cached directory
clean:
	cmake --build build --target clean
	ruff clean
