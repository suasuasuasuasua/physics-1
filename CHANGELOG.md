## 1.0.6 (2025-11-07)

### Fix

- add commitizen recipe and depenency

## 1.0.5 (2025-11-07)

### Fix

- **cmake**: disable C++ extensions

## 1.0.4 (2025-11-07)

### Fix

- **ci**: reduce complexity of on-push file paths
- **tests**: disable gmock builds
- **ci**: build on CMakeLists.txt changes too
- **ci**: only build on changes to build inputs

## 1.0.3 (2025-11-07)

### Fix

- **ci**: remove condition entirely

## 1.0.2 (2025-11-07)

## 1.0.1 (2025-11-07)

## 1.0.0 (2025-11-07)

### Refactor

- rename project as phys instead of physics_1

## 0.2.9 (2025-11-07)

### Fix

- **tests**: fix broken tests on string output change

## 0.2.8 (2025-11-05)

### Fix

- **ci**: skip musllinux for macos builds

## 0.2.7 (2025-11-05)

### Fix

- **ci**: use correct tag for cibuildwheel

## 0.2.6 (2025-11-05)

### Fix

- **ci**: only build for manylinux

## 0.2.5 (2025-11-05)

### Fix

- **python**: reduce dependency on heavier python modules

## 0.2.4 (2025-11-04)

### Fix

- **python**: experiment with non-required and required

## 0.2.3 (2025-11-04)

### Fix

- **ci**: add test suite path

## 0.2.2 (2025-11-04)

### Fix

- **python**: experiment with disable python requirement

## 0.2.1 (2025-11-04)

### Fix

- **ci**: recursively clone submodules

## 0.2.0 (2025-11-04)

### Feat

- **linalg/vector**: add magnitude and angle constructor
- **linalg/vector**: add angle methods for Vector2
- **linalg/vector**: add division, mag, and unit methods
- initial commit

### Fix

- **python**: update stubs for functions
- **lint**: exlcude extern and pyi files
- **math/linalg**: fix setters for Vector2
- **pyproject**: reduce complexity of packages wheel
- add .envrc for devenv
- **python**: generate more stubs for Vector2
- **linalg/vector**: remove double space in toString
- **README**: correct spelling for compiler
- **Makefile**: correct the stubgen command
- **build**: relax requirements to python3.11
- **ci**: use better quotes on python versions matrix
- **build**: remove sources from python_add_library for simplicity
- **build**: add embed module for pybind11 to also get dev headers
- **build**: add pybind11 headers back for compile-time
- **CMakeLists.txt**: remove find_package for Python in CMakeLists (#4)
- **ci**: remove dev group from test workflow
- **ci**: add the testing group for last stage
- **ci**: use bar to split command line
- **ci**: correct pip group call
- **ci**: build the tests first
- **ci**: submodules not submodule
- **ci**: recursively checkout submodules
- **example**: wrap in a guard header
- **Makefile**: lint the header files
- **build**: force a new reinstall each time
- **CMakeLists.txt**: remove pthread linking
- **build**: manually define project name and version in CMakeLists.txt
- **pyproject**: update typo in physics
- **Makefile**: use ruff clean

### Refactor

- **math/linalg**: use def_property idiom for x and y
- **build**: use library linking instead of double compilation
- **math/linalg**: nest linalg library under math
- further move CMake files into testing and python folders
- nest the namespace under math and add constants header
- **linalg/vector**: snake case the string method
- **python**: use stubgen structure
- **linalg**: use shorthand for vector2s
- move python code to separate folder
- **build**: further modularize the CMakeLists.txt files
- **tests**: modularize the CMakeLists.txt file for testing
- **tests**: move util file to python tests folder
- **src**: move functions example to folder
- move the testing functions to inc and src structure
- **build**: rename dist stage to wheel
