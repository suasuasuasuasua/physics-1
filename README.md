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

The `build.ninja` file has the following utility functions.

```bash
# build the python package
ninja build

# install the python package
ninja install

# build the python wheel file
ninja wheel

# run tests in the tests/ folder
ninja test

# clean the cached directory
ninja clean

# build container (defaults to x86_64)
ninja build-container

# build container for aarch64
PLATFORM_ARCH=aarch64 ninja build-container
```

## Course Material

- [MIT Course Wave](https://ocw.mit.edu/courses/8-01sc-classical-mechanics-fall-2016/)

## References

- [pybind11 Documentation](https://pybind11.readthedocs.io/en/stable/)
- The CMake example from [scikit](https://github.com/pybind/scikit_build_example)
