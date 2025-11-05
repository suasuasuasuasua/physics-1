This is a C++ based repository with a pybind11 setup to export Python bindings.
The purpose of this project is for me to learn both C++ and Python and physics
at the same time.

## Setup

- Install developer dependencies with `pip install --group dev --group test
--group build`

## Code Standards

### Required Before Each Commit

- Run `make ci` before committing any changes to ensure proper code formatting
and that unit tests are still passing
- Run `make stubs` to autogenerate any additional python stubs from the pybind11
integration

### Development Flow

These are important Makefile commands

- Build: `make build`
- Install: `make install` to build and install the C++ backend and python
package
- Test: `make test`
- Clean: `make clean`
    - Full clean: `make clean-full`

## Repository Structure
- `src/`: main code for the physics and math engine
- `inc/`: includes for the source files
- `notes/`: my notes on physics
    - do not touch this one
- `tests/`: the unit tests
- `python/`: the python binding code
- `extern/`: external dependencies like googletest and pybind11
    - do not touch this one

## Key Guidelines
1. Follow C++ and Python best practices and idiomatic patterns
2. Maintain existing code structure and organization
3. Write unit tests for new functionality
4. Document public APIs and complex logic. Suggest changes to the `docs/` folder
   when appropriate
5. Little to no external dependencies
