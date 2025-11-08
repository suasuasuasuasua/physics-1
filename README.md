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

The `build.sh` script provides all build and development tasks:

```bash
# build the python package
./build.sh build

# install the python package
./build.sh install

# build the python wheel file
./build.sh wheel

# run tests in the tests/ folder
./build.sh test

# clean the cached directory
./build.sh clean

# full clean (remove build directory)
./build.sh clean-full

# run all CI tasks (build, format, lint, test)
./build.sh ci

# format code
./build.sh format

# lint code
./build.sh lint

# build container (defaults to x86_64)
./build.sh build-container

# build container for aarch64
./build.sh build-container aarch64

# show all available commands
./build.sh help
```

## Course Material

- [MIT Course Wave](https://ocw.mit.edu/courses/8-01sc-classical-mechanics-fall-2016/)

## References

- [pybind11 Documentation](https://pybind11.readthedocs.io/en/stable/)
- The CMake example from [scikit](https://github.com/pybind/scikit_build_example)
