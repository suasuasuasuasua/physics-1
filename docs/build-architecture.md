# Build Architecture Documentation

This document explains how the physics_1 project's build system works, connecting Python and C++ code through pybind11 and scikit-build-core.

## Table of Contents

1. [Overview](#overview)
2. [Key Components](#key-components)
3. [Build Flow](#build-flow)
4. [Package Structure](#package-structure)
5. [How It All Works Together](#how-it-all-works-together)
6. [Common Operations](#common-operations)

## Overview

The physics_1 project is a **hybrid Python/C++ package** that uses:
- **C++** for performance-critical physics computations
- **Python** as the user-facing interface
- **pybind11** to bridge C++ and Python
- **scikit-build-core** to orchestrate the build process
- **CMake** to compile the C++ code

The magic happens when you run `pip install .` - scikit-build-core automatically invokes CMake to compile your C++ code and packages it as a Python module.

## Key Components

### 1. `pyproject.toml` - The Python Build Configuration

This is the **entry point** that pip reads to understand how to build your package.

```toml
[build-system]
requires = ["scikit-build-core", "pybind11"]
build-backend = "scikit_build_core.build"
```

**What this means:**
- `requires`: Lists build-time dependencies (scikit-build-core and pybind11)
- `build-backend`: Tells pip to use `scikit_build_core.build` instead of the default Python build system
- When you run `pip install .`, pip loads scikit-build-core, which then:
  1. Reads your `CMakeLists.txt`
  2. Runs CMake to configure and build your C++ code
  3. Collects the compiled `.so` files and Python files
  4. Packages everything into a wheel

**The rest of pyproject.toml:**
```toml
[project]
name = "physics_1"
version = "0.1.0"
```
This defines your package metadata (name, version, dependencies, etc.)

### 2. `CMakeLists.txt` - The C++ Build Configuration

This is what scikit-build-core reads to compile your C++ code.

#### Key CMake Commands Explained:

```cmake
project(physics_1 VERSION 0.1.0 LANGUAGES CXX)
```
- Defines your CMake project name and version

```cmake
set(PYBIND11_FINDPYTHON ON)
add_subdirectory(extern/pybind11)
```
- Tells pybind11 to find the same Python interpreter that pip is using
- Includes pybind11's CMake scripts from the git submodule

```cmake
python_add_library(_core MODULE 
    src/main.cpp 
    src/example/functions.cpp
    src/linalg/vector.cpp 
    WITH_SOABI)
```
**This is the crucial command!**
- `python_add_library`: A pybind11 CMake function that creates a Python extension module
- `_core`: The name of the compiled module (will become `_core.so` or `_core.pyd`)
- `MODULE`: Indicates this is a loadable Python module (not a static library)
- `WITH_SOABI`: Adds platform-specific suffix (e.g., `_core.cpython-312-x86_64-linux-gnu.so`)
- Lists all `.cpp` files to compile together

```cmake
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(_core PRIVATE "${CMAKE_SOURCE_DIR}/inc/")
target_link_libraries(_core PRIVATE pybind11::headers)
```
- Passes the version as a compile-time define
- Tells the compiler where to find header files (`inc/` directory)
- Links against pybind11 headers

```cmake
install(TARGETS _core DESTINATION physics_1)
```
**This determines where the compiled module goes!**
- Installs `_core.so` into the `physics_1/` directory in the wheel
- This is why your Python package imports it as `from physics_1._core import ...`

### 3. `src/main.cpp` - The pybind11 Bridge

This file creates the Python module from C++ code.

```cpp
PYBIND11_MODULE(_core, m, py::mod_gil_not_used(),
                py::multiple_interpreters::per_interpreter_gil()) {
    m.doc() = R"pbdoc(
        Physics 1 Module
        ...
    )pbdoc";

    example::init_example(m);
    linalg::init_linalg(m);
}
```

**Breaking it down:**
- `PYBIND11_MODULE(_core, m, ...)`: Defines a Python module named `_core`
  - The name `_core` must match what you specified in `python_add_library`
- `m`: The module object that Python will see
- `example::init_example(m)`: Calls your C++ function to register the `example` submodule
- `linalg::init_linalg(m)`: Calls your C++ function to register the `linalg` submodule

In `src/example/functions.cpp`:
```cpp
void init_example(py::module_ &m) {
    m.def_submodule("example", "Some example functions demoing pybind11")
        .def("add", &example::add, py::arg("i"), py::arg("j"), R"pbdoc(
            Add two numbers
        )pbdoc")
        .def("sub", &example::sub, py::arg("i"), py::arg("j"), R"pbdoc(
            Subtract two numbers
        )pbdoc");
}
```
- `def_submodule("example", ...)`: Creates `_core.example` submodule
- `.def("add", &example::add, ...)`: Exposes C++ function `example::add` as Python function

### 4. `src/physics_1/__init__.py` - The Python Package Interface

This is the **user-facing Python module** that imports from the compiled C++ module.

```python
from __future__ import annotations
from ._core import __doc__, __version__, example, linalg

__all__ = ["__doc__", "__version__", "example", "linalg"]
```

**What's happening:**
1. Python looks for `physics_1/__init__.py` when you do `import physics_1`
2. This file imports from `._core` (the compiled C++ module)
3. Re-exports `example` and `linalg` so users can do:
   ```python
   import physics_1
   physics_1.example.add(1, 2)
   physics_1.linalg.Vector2D(1.0, 2.0)
   ```

## Build Flow

Here's what happens when you run `pip install .`:

```
pip install .
    ↓
1. pip reads pyproject.toml
    ↓
2. pip sees build-backend = "scikit_build_core.build"
    ↓
3. pip invokes scikit-build-core
    ↓
4. scikit-build-core finds CMakeLists.txt
    ↓
5. scikit-build-core runs: cmake -S . -B build
    ↓
6. CMake processes CMakeLists.txt:
   - Finds Python interpreter
   - Loads pybind11
   - Configures compilation of _core module
    ↓
7. scikit-build-core runs: cmake --build build
    ↓
8. C++ compiler compiles:
   - src/main.cpp
   - src/example/functions.cpp
   - src/linalg/vector.cpp
    ↓
9. Linker creates: _core.cpython-312-x86_64-linux-gnu.so
    ↓
10. CMake install step copies:
    - _core.so → wheel/physics_1/
    - src/physics_1/*.py → wheel/physics_1/
    - src/physics_1/*.pyi → wheel/physics_1/
    ↓
11. scikit-build-core packages everything into a wheel
    ↓
12. pip installs the wheel to your Python environment
```

## Package Structure

The `src/physics_1/` directory must be structured carefully because of how Python imports work:

```
src/physics_1/
├── __init__.py          # Makes physics_1 a Python package
├── __init__.pyi         # Type hints for the main module
├── example.pyi          # Type hints for example submodule
└── linalg.pyi           # Type hints for linalg submodule

(After building)
└── _core.so             # Compiled C++ extension (installed by CMake)
```

### Why This Structure is Required

1. **`__init__.py` is mandatory**: Python requires this file to treat `physics_1` as a package
2. **CMake installs `_core.so` here**: The `install(TARGETS _core DESTINATION physics_1)` in CMakeLists.txt places the compiled module in this directory
3. **Import paths must match**: When `__init__.py` does `from ._core import example`, Python looks for `_core.so` in the same directory

### Why It Feels Fragile

The system has several moving parts that must align:
- Module name in `PYBIND11_MODULE(_core, m, ...)` 
- Module name in `python_add_library(_core ...)`
- Module name in `install(TARGETS _core DESTINATION physics_1)`
- Import statement in `__init__.py`: `from ._core import ...`
- Directory name: `src/physics_1/`

**If any of these don't match, imports will fail!**

## Stub Files (`.pyi`)

### What Are They?

Stub files provide type hints for your compiled C++ code. They help:
- IDEs provide autocomplete
- Type checkers like mypy verify code
- Users understand function signatures

### Why Generate Them?

When you write C++ and expose it with pybind11:
- Python sees the functions but doesn't know their types
- IDEs can't autocomplete
- Type checkers can't validate usage

### How to Generate

```bash
make stubs
# or
python -m pybind11-stubgen --output src physics_1
```

This:
1. Imports your compiled `_core` module
2. Inspects it using Python's introspection
3. Generates `.pyi` files with type annotations

**Example output** (`example.pyi`):
```python
def add(i: typing.SupportsInt, j: typing.SupportsInt) -> int:
    """Add two numbers"""
```

### Manual Maintenance

While pybind11-stubgen helps, you may need to:
- Fix incorrect type hints
- Add more detailed documentation
- Handle complex types that the generator misses

This is why it feels tedious - it's semi-automated but requires review.

## How It All Works Together

### The Connection Map

```
pyproject.toml
    ↓ (tells pip to use)
scikit-build-core
    ↓ (invokes)
CMakeLists.txt
    ↓ (compiles)
src/main.cpp + src/example/*.cpp + src/linalg/*.cpp
    ↓ (produces)
_core.so
    ↓ (installed to)
src/physics_1/_core.so
    ↑ (imported by)
src/physics_1/__init__.py
    ↑ (imported by users)
import physics_1
```

### The Key Insight

**scikit-build-core is the glue** that makes `pip install .` understand CMake:
- Without it, pip wouldn't know how to invoke CMake
- It bridges the Python packaging world and the C++ build world
- It's specifically designed for projects mixing Python and C++

## Common Operations

### Building the C++ Code Directly

```bash
make build
# or
cmake -S . -B build
cmake --build build
```
This builds `_core.so` in the `build/` directory but **doesn't install it** into the Python package.

### Installing as a Python Package

```bash
make install
# or
pip install . --no-deps --force-reinstall
```
This:
1. Runs the full build process
2. Creates a wheel with `_core.so` in the right place
3. Installs it to your Python environment

### Building a Wheel for Distribution

```bash
make wheel
# or
python -m build --wheel
```
Creates a `.whl` file in `dist/` that you can share or upload to PyPI.

### Running Tests

```bash
# C++ tests (using GoogleTest)
make test-cpp
# or
cd build && ctest

# Python tests (using pytest)
make test-python
# or
python -m pytest
```

### Generating Type Stubs

```bash
make stubs
# or
python -m pybind11-stubgen --output src physics_1
```

## Troubleshooting

### Import Errors

If you get `ModuleNotFoundError: No module named '_core'`:
- Check that CMake actually installed `_core.so` to `src/physics_1/`
- Verify the `install(TARGETS _core DESTINATION physics_1)` line in CMakeLists.txt
- Try `pip install . --force-reinstall`

### Build Failures

If CMake can't find pybind11:
- Initialize submodules: `git submodule update --init --recursive`
- Check that `extern/pybind11/CMakeLists.txt` exists

If compilation fails:
- Check that you have a C++17 compatible compiler
- Verify all `.cpp` files are listed in `python_add_library`
- Check that `inc/` directory is in the include path

### Type Hints Not Working

If stubs don't reflect your API:
- Regenerate: `make stubs`
- Manually edit the `.pyi` files
- Make sure `.pyi` files are in the same directory as `__init__.py`

## References

- [pybind11 Documentation](https://pybind11.readthedocs.io/)
- [scikit-build-core Documentation](https://scikit-build-core.readthedocs.io/)
- [CMake Documentation](https://cmake.org/documentation/)
- [Python Packaging User Guide](https://packaging.python.org/)
