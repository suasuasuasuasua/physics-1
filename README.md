# Physics

> A repository dedicated to me learning physics from the ground up.

I have always been interested in physics, but I've only ever taken two classes
in my time at college (physics 1 and 2). Though I did well, I don't feel like I
truly grasped the material; I only learned how to take tests and do homework.

This repository has a few goals

- Work through an undergraduate level physics class at my own pace to fully
understand the material - Improve my C++ skills outside of work
- Work through and implement the practice problems as test cases to ensure that
my code works

## Quick Start

Ensure that these programs are installed.

```text
cmake
gcc (or any C/C++ compiler like clang)
ninja
python3.13
```

See `devenv.nix` for automatic installation using `nix`.

### Using the Build Script

The `setup.py` script provides all build and development tasks with support for subcommands and flags:

```bash
# build the python package
python3 setup.py build

# install the python package
python3 setup.py install

# build the python wheel file
python3 setup.py wheel

# run tests in the tests/ folder
python3 setup.py test

# run tests with verbose output
python3 setup.py test --verbose

# clean the cached directory
python3 setup.py clean

# full clean (remove build directory)
python3 setup.py clean-full

# run all CI tasks (build, format, lint, test)
python3 setup.py ci

# format code
python3 setup.py format

# lint code
python3 setup.py lint

# build container (defaults to x86_64)
python3 setup.py build-container

# build container for aarch64
python3 setup.py build-container --platform aarch64

# show all available commands and options
python3 setup.py --help

# show help for a specific command
python3 setup.py build-container --help
```

## Course Material

- [MIT Course Wave](https://ocw.mit.edu/courses/8-01sc-classical-mechanics-fall-2016/)

## References

- [pybind11 Documentation](https://pybind11.readthedocs.io/en/stable/)
- The CMake example from [scikit](https://github.com/pybind/scikit_build_example)
