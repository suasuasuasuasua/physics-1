# Physics 1

> A repository dedicated to me learning physics from the ground up.

I have always been interested in physics, but I've only ever taken two classes
in my time at college (physics 1 and 2). Though I did well, I don't feel like I
truly grasped the material; I only learned how to take tests and do homework.

This repository has a few goals

- Work through an undergraduate level physics class at my own pace to fully
understand the material
- Improve my C++ skills outside of work
- Work through and implement the practice problems as test cases to ensure that
my code works

## Quick Start

Ensure that these programs are installed.

```text
cmake
gcc (or any C/C++ copmiler like clang)
make
python3.13
```

See `devenv.nix` for automatic installation using `nix`.

The `Makefile` has the following utility functions.

```bash
# build the python package
make 

# build with code coverage enabled
make build-coverage

# install the python package
make install

# build the python wheel file
make dist

# run tests in the tests/ folder
make test

# run tests with coverage collection
make test-coverage

# generate C++ coverage report (after running tests with coverage)
make coverage-report

# clean the cached directory
make clean
```

## Code Coverage

This project includes code coverage metrics for both C++ and Python code:

- **Python Coverage**: Uses `pytest-cov` to generate coverage reports
- **C++ Coverage**: Uses `gcov`/`gcovr` with CMake's `--coverage` flag
- **GitHub Integration**: Automatically uploads coverage to Codecov on CI runs

To run tests with coverage locally:
```bash
make build-coverage  # Build with coverage instrumentation
make test-coverage   # Run tests with coverage
make coverage-report # Generate coverage report
```

Coverage reports are generated in Cobertura XML format:
- `coverage.xml` - Python coverage
- `coverage-cpp.xml` - C++ coverage

## Course Material

- [MIT Course Wave](https://ocw.mit.edu/courses/8-01sc-classical-mechanics-fall-2016/)

## References

- [pybind11 Documentation](https://pybind11.readthedocs.io/en/stable/)
- The CMake example from [scikit](https://github.com/pybind/scikit_build_example)
