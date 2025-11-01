# FAQ and Troubleshooting Guide

Common questions and issues when working with the physics_1 build system.

## Frequently Asked Questions

### Q: Why do I need scikit-build-core? Why can't I just use setuptools?

**A:** Setuptools doesn't natively understand CMake. When you have C++ code that needs to be compiled, you need a build system that can:
1. Invoke CMake to compile your C++ code
2. Link against pybind11
3. Package the compiled `.so` files in the right location
4. Create a proper Python wheel

scikit-build-core specifically bridges the CMake world and the Python packaging world. It understands both CMakeLists.txt and pyproject.toml.

**Alternative approaches:**
- setuptools + custom build commands (more manual work)
- pybind11's built-in setuptools integration (older, less flexible)
- scikit-build (older version, now superseded by scikit-build-core)

### Q: What's the difference between `make build` and `pip install .`?

**A:** These do different things:

**`make build`** (or `cmake -S . -B build && cmake --build build`):
- Only compiles the C++ code
- Creates `_core.so` in the `build/` directory
- Does NOT install anything to your Python environment
- Useful for C++ development and testing
- Can run C++ tests with `ctest`

**`pip install .`**:
- Invokes scikit-build-core which invokes CMake
- Compiles C++ code
- Installs `_core.so` to the correct Python package location
- Copies Python files (`__init__.py`, `.pyi` files)
- Installs the package to your Python environment
- Now you can `import physics_1` from anywhere

**When to use which:**
- Use `make build` for C++ development and testing
- Use `pip install .` when you want to use the Python package

### Q: Why is the compiled module called `_core` with an underscore?

**A:** This is a Python convention:
- Modules starting with `_` are considered "private" or "internal"
- `_core` is the compiled C++ extension (implementation detail)
- `physics_1` is the public Python package that users import
- `__init__.py` re-exports from `_core`, hiding the implementation

**Benefits:**
- You can reorganize the C++ code without changing the public API
- You can add pure Python code alongside C++ code
- Users don't need to know they're calling C++ functions

**Example:**
```python
# Without the wrapper (users import compiled module directly)
import physics_1._core
physics_1._core.example.add(1, 2)  # Exposes internal structure

# With the wrapper (clean API)
import physics_1
physics_1.example.add(1, 2)  # Clean, implementation-agnostic
```

### Q: What is WITH_SOABI and why is it needed?

**A:** SOABI stands for "Shared Object Application Binary Interface"

```cmake
python_add_library(_core MODULE src/main.cpp WITH_SOABI)
```

**What it does:**
- Adds platform-specific suffix to the compiled module
- Without it: `_core.so`
- With it: `_core.cpython-312-x86_64-linux-gnu.so`

**Why it's needed:**
- Different Python versions have different ABIs (binary interfaces)
- Different platforms (Linux, Windows, macOS) have different formats
- The suffix ensures the right module is loaded for your Python version
- Prevents accidentally using a module compiled for Python 3.11 with Python 3.12

**The filename tells you:**
- `cpython`: CPython interpreter (vs PyPy, etc.)
- `312`: Python 3.12
- `x86_64`: 64-bit architecture
- `linux-gnu`: Linux platform

### Q: Why do I need git submodules for pybind11 and googletest?

**A:** Git submodules let you include external projects in your repository.

**Why submodules instead of pip packages:**
- **pybind11**: You need its CMake integration, not just the Python package
- **googletest**: Pure C++ library, not available via pip
- Both need to be available at build time, not runtime

**Initialization required:**
```bash
git submodule update --init --recursive
```

**Benefits:**
- Pinned to specific versions
- Works offline (once cloned)
- CMake can `add_subdirectory()` directly

**Alternatives:**
- FetchContent in CMake (downloads at configure time)
- System packages (less portable)
- Manual installation (more work for contributors)

### Q: Why is the repository named "physics-1" but the package is "physics_1"?

**A:** Git repository names can use hyphens, but Python package names should use underscores.

**Naming conventions:**
- **Repository name**: `physics-1` (hyphens are fine in URLs and filesystem)
- **Python package name**: `physics_1` (underscores, as hyphens aren't valid in Python identifiers)

**Why this matters:**
```python
# This wouldn't work if package was named physics-1:
import physics-1  # SyntaxError: invalid syntax
physics-1.example.add(1, 2)  # Python treats hyphen as minus operator

# With underscore, it works:
import physics_1  # Valid Python identifier
physics_1.example.add(1, 2)  # Works correctly
```

**Consistency:**
- Repository: `physics-1` (in GitHub URL, git clone, etc.)
- Package directory: `src/physics_1/`
- pyproject.toml: `name = "physics_1"`
- Python imports: `import physics_1`

### Q: Why is the directory structure so specific?

**A:** Python's import system requires specific structure:

```
src/physics_1/          ← Must match package name in pyproject.toml
├── __init__.py         ← REQUIRED for Python to see it as a package
├── _core.so            ← Must be in same dir for "from . import _core"
└── *.pyi               ← Type hints, must be with code
```

**The rules:**
1. `__init__.py` is mandatory for a directory to be a Python package
2. Relative imports (`from .`) only work within a package
3. CMake's `install(DESTINATION physics_1)` must match the directory name
4. The directory must be under `src/` for scikit-build-core to find it

**What breaks if you change it:**
- Move `_core.so` elsewhere → ImportError: cannot import name '_core'
- Remove `__init__.py` → ModuleNotFoundError: No module named 'physics_1'
- Rename directory → Package not found by scikit-build-core

### Q: What are .pyi files and do I really need them?

**A:** `.pyi` files are "stub files" - they contain type hints only, no implementation.

**What they provide:**
```python
# example.pyi
def add(i: int, j: int) -> int: ...
```

**Benefits:**
- IDE autocomplete: Your editor knows `add()` takes two ints
- Type checking: mypy/pyright can verify your code
- Documentation: Users can see signatures without docs

**Do you need them:**
- **For development:** Highly recommended (makes coding much easier)
- **For distribution:** Nice to have (better user experience)
- **For runtime:** No - Python doesn't read them at runtime

**Without stub files:**
```python
# Your IDE doesn't know what add() accepts
result = physics_1.example.add("hello", "world")  # No warning!
# Runtime error when C++ tries to convert strings to ints
```

**With stub files:**
```python
result = physics_1.example.add("hello", "world")  # IDE shows error!
# Caught before running
```

### Q: Why do I need to regenerate stubs manually? Can't it be automatic?

**A:** Stub generation requires importing your module, which requires it to be compiled and installed:

**The catch-22:**
1. You need stubs for development
2. Generating stubs requires `import physics_1`
3. Importing requires the module to be installed
4. Installing requires compilation
5. After any C++ changes, stubs may be outdated

**Current workflow:**
```bash
# 1. Make C++ changes
vim src/example/functions.cpp

# 2. Install to Python
pip install . --force-reinstall

# 3. Regenerate stubs
make stubs

# 4. Review and commit .pyi files
git add src/physics_1/*.pyi
```

**Why not automatic:**
- pybind11-stubgen sometimes generates incorrect types
- You may want to add more detailed documentation
- Some complex types need manual intervention
- Stubs are committed to source control (so others don't need to generate them)

**Best practice:**
- Generate stubs after finalizing your C++ API
- Review the generated `.pyi` files
- Manually fix any issues
- Commit them to git so others get the benefits

### Q: Can I mix pure Python code with C++ code?

**A:** Absolutely! That's one of the advantages of this structure.

**Example - Adding a pure Python utility:**

```python
# src/physics_1/utils.py
def degrees_to_radians(degrees):
    import math
    return degrees * math.pi / 180

# src/physics_1/__init__.py
from ._core import __doc__, __version__, example, linalg
from . import utils  # ← Add this

__all__ = ["__doc__", "__version__", "example", "linalg", "utils"]
```

Now users can:
```python
import physics_1
physics_1.utils.degrees_to_radians(90)
```

**Use cases:**
- Python wrapper functions around C++ code
- Utility functions that don't need C++ performance
- Higher-level APIs built on C++ primitives
- Pure Python implementations for testing

### Q: How do I debug C++ code called from Python?

**A:** Several approaches:

**1. Print debugging:**
```cpp
void my_function(int x) {
    std::cout << "my_function called with x=" << x << std::endl;
    // your code
}
```

**2. Using GDB:**
```bash
# Install with debugging symbols
CFLAGS="-O0 -g" pip install . --force-reinstall

# Run Python under GDB
gdb --args python -c "import physics_1; physics_1.example.add(1, 2)"

# In GDB:
(gdb) break example::add
(gdb) run
(gdb) step
```

**3. Using print in pybind11:**
```cpp
#include <pybind11/iostream.h>

void my_function() {
    py::print("Debug message from C++");
}
```

**4. C++ tests (better for development):**
```bash
# Write GoogleTest tests
# tests/cpp/test_example.cpp

# Run directly
make build
cd build
ctest --output-on-failure
```

### Q: What's the difference between headers in `inc/` and implementation in `src/`?

**A:** Classic C++ separation:

**Headers (`inc/`):**
- Declarations (function signatures, class definitions)
- Included by multiple `.cpp` files
- Included via `#include <example/functions.h>`
- Used at compile time to check types

**Implementation (`src/`):**
- Function definitions (actual code)
- Each `.cpp` compiled separately
- Combined by linker into `_core.so`

**Example:**

```cpp
// inc/example/functions.h
namespace example {
    int add(int i, int j);  // ← Declaration
}

// src/example/functions.cpp
#include <example/functions.h>
namespace example {
    int add(int i, int j) {  // ← Definition
        return i + j;
    }
}
```

**Why separate:**
- Multiple files can include the same header
- Only compile implementation once
- Change implementation without recompiling files that include the header
- Reduces build times for large projects

**CMake setup:**
```cmake
target_include_directories(_core PRIVATE "${CMAKE_SOURCE_DIR}/inc/")
```
This tells the compiler where to find headers when you write `#include <example/functions.h>`

## Troubleshooting

### Issue: ModuleNotFoundError: No module named 'physics_1'

**Cause:** Package not installed to your Python environment

**Solutions:**
```bash
# Install the package
pip install .

# Or for development (changes reflected immediately)
pip install -e .

# Force reinstall if it's already installed
pip install . --force-reinstall

# Check if it's installed
pip list | grep physics_1
```

### Issue: ImportError: cannot import name '_core' from 'physics_1'

**Cause:** `_core.so` not in the right location or not compiled

**Debug steps:**
```bash
# 1. Find where physics_1 is installed
python -c "import physics_1; print(physics_1.__file__)"

# 2. List files in that directory
ls -la /path/to/site-packages/physics_1/

# 3. Look for _core.so (or _core.cpython-*.so)
# If missing, reinstall:
pip install . --force-reinstall
```

**Common causes:**
- CMake `install(DESTINATION)` doesn't match package name
- Build failed but pip didn't notice
- Wrong Python environment activated

### Issue: CMake Error: add_subdirectory ... does not contain a CMakeLists.txt

**Cause:** Git submodules not initialized

**Solution:**
```bash
git submodule update --init --recursive

# Verify
ls extern/pybind11/CMakeLists.txt
ls extern/googletest/CMakeLists.txt
```

### Issue: Function added to C++ but not visible in Python

**Checklist:**
```bash
# 1. Did you expose it in pybind11?
# Check src/example/functions.cpp for .def("your_func", ...)

# 2. Did you rebuild and reinstall?
pip install . --force-reinstall

# 3. Restart Python interpreter
python
>>> import physics_1
>>> dir(physics_1.example)  # Should list your function

# 4. Regenerate stubs for IDE autocomplete
make stubs
```

### Issue: Changes to C++ not reflected in Python

**Problem:** Old compiled module cached

**Solution:**
```bash
# Force rebuild
pip install . --force-reinstall --no-deps

# Or clear cache manually
rm -rf build/
pip cache purge
pip install .

# Restart Python interpreter (important!)
```

### Issue: Type hints in .pyi don't match actual function

**This is normal!** pybind11-stubgen isn't perfect.

**Solution:**
```bash
# Regenerate
make stubs

# Manually edit .pyi file
vim src/physics_1/example.pyi

# Fix incorrect types
# Example: Change SupportsInt to int if that's more accurate
def add(i: int, j: int) -> int:  # ← Fixed
    """Add two numbers"""
```

### Issue: Segfault or crash when calling C++ from Python

**Common causes:**

**1. Returning reference to local variable:**
```cpp
// BAD
const std::string& bad_func() {
    std::string local = "hello";
    return local;  // ← Returns reference to destroyed variable
}

// GOOD
std::string good_func() {
    std::string local = "hello";
    return local;  // ← Returns copy
}
```

**2. Invalid memory access:**
```cpp
// BAD
void process(const std::vector<int>& vec) {
    vec[1000];  // ← May be out of bounds
}

// GOOD
void process(const std::vector<int>& vec) {
    if (vec.size() > 1000) {
        vec[1000];
    }
}
```

**Debug with:**
```bash
# Compile with sanitizers
CFLAGS="-fsanitize=address" pip install . --force-reinstall

# Run under GDB
gdb --args python -c "import physics_1; physics_1.example.crash_func()"
```

### Issue: Build works on my machine but not in CI

**Common causes:**

**1. Missing dependencies:**
```yaml
# .github/workflows/test.yml
- name: Install dependencies
  run: |
    pip install build pytest
    git submodule update --init --recursive
```

**2. Python version mismatch:**
```yaml
- uses: actions/setup-python@v4
  with:
    python-version: '3.13'  # ← Must match requires-python in pyproject.toml
```

**3. Compiler not available:**
```yaml
# For Ubuntu
- name: Install compiler
  run: sudo apt-get install -y build-essential cmake
```

### Issue: Wheel built on Linux doesn't work on macOS

**Cause:** Binary wheels are platform-specific

**Solution:**
Build separately for each platform:
```bash
# On Linux
python -m build --wheel
# Creates: physics_1-0.1.0-cp313-cp313-linux_x86_64.whl

# On macOS
python -m build --wheel
# Creates: physics_1-0.1.0-cp313-cp313-macosx_11_0_arm64.whl

# On Windows
python -m build --wheel
# Creates: physics_1-0.1.0-cp313-cp313-win_amd64.whl
```

**For distribution:**
- Use cibuildwheel in CI to build for multiple platforms
- Or distribute source distribution and let users compile

## Best Practices

### 1. Development Workflow

```bash
# Initial setup
git clone <repo>
cd physics-1  # Note: repo name has hyphen, package name is physics_1 with underscore
git submodule update --init --recursive
pip install -e .  # Editable install

# Daily development
# Edit C++ code
vim src/example/functions.cpp

# Rebuild
pip install -e . --force-reinstall --no-deps

# Test
python -c "import physics_1; physics_1.example.add(1, 2)"

# Regenerate stubs periodically
make stubs
```

### 2. Before Committing

```bash
# Format code
make format

# Lint
make lint

# Run all tests
make test

# Regenerate stubs if API changed
make stubs

# Commit
git add .
git commit -m "Add new physics functions"
```

### 3. Adding New Functionality

**Order of operations:**
1. Write C++ header (`inc/module/file.h`)
2. Write C++ implementation (`src/module/file.cpp`)
3. Write C++ tests (`tests/cpp/test_module.cpp`)
4. Test C++ code: `make build && make test-cpp`
5. Expose to Python in `init_module()` function
6. Update CMakeLists.txt to include new .cpp file
7. Update `src/physics_1/__init__.py` if adding new submodule
8. Install: `pip install . --force-reinstall`
9. Write Python tests (`tests/python/test_module.py`)
10. Test Python code: `make test-python`
11. Regenerate stubs: `make stubs`
12. Commit everything including .pyi files

### 4. Performance Tips

**Build faster:**
```bash
# Parallel builds
cmake --build build -j$(nproc)

# Or set in CMakeLists.txt
set(CMAKE_BUILD_PARALLEL_LEVEL 8)
```

**Incremental builds:**
```bash
# Don't clean build directory unnecessarily
# CMake tracks changes and only rebuilds what's needed
make build  # Fast incremental build
```

**Use ccache:**
```bash
# Install
sudo apt-get install ccache

# Configure CMake
cmake -S . -B build -DCMAKE_CXX_COMPILER_LAUNCHER=ccache

# Subsequent builds much faster
```

## Resources

- [pybind11 Documentation](https://pybind11.readthedocs.io/)
- [scikit-build-core Documentation](https://scikit-build-core.readthedocs.io/)
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/)
- [Python Packaging Guide](https://packaging.python.org/)
- [pybind11 FAQ](https://pybind11.readthedocs.io/en/stable/faq.html)
