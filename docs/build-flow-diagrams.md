# Build Flow Visual Diagrams

This document provides visual representations of how the build system works.

## Component Relationship Diagram

```
┌─────────────────────────────────────────────────────────────────────┐
│                         USER COMMAND                                 │
│                       $ pip install .                                │
└─────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────┐
│                      pyproject.toml                                  │
│  ┌───────────────────────────────────────────────────────────────┐  │
│  │ [build-system]                                                 │  │
│  │ requires = ["scikit-build-core", "pybind11"]                  │  │
│  │ build-backend = "scikit_build_core.build"  ← CRITICAL!       │  │
│  └───────────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────┐
│                    scikit-build-core                                 │
│  (Acts as translator between pip and CMake)                          │
│  • Reads CMakeLists.txt                                              │
│  • Invokes CMake to build C++ code                                   │
│  • Packages compiled code with Python files                          │
└─────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────┐
│                      CMakeLists.txt                                  │
│  ┌───────────────────────────────────────────────────────────────┐  │
│  │ add_subdirectory(extern/pybind11)                             │  │
│  │                                                                │  │
│  │ python_add_library(_core MODULE                               │  │
│  │     src/main.cpp                                               │  │
│  │     src/example/functions.cpp                                  │  │
│  │     src/linalg/vector.cpp                                      │  │
│  │     WITH_SOABI)                                                │  │
│  │                                                                │  │
│  │ install(TARGETS _core DESTINATION physics_1)                  │  │
│  └───────────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────────┘
                                    │
                    ┌───────────────┴───────────────┐
                    ▼                               ▼
        ┌─────────────────────┐       ┌─────────────────────┐
        │   C++ Compilation   │       │  pybind11 Headers   │
        │                     │       │                     │
        │  • src/main.cpp     │       │  • Provides macros  │
        │  • functions.cpp    │◄──────┤  • Type conversion  │
        │  • vector.cpp       │       │  • Module creation  │
        │  • inc/*.h          │       │                     │
        └─────────────────────┘       └─────────────────────┘
                    │
                    ▼
        ┌─────────────────────┐
        │  Compiled Binary     │
        │                     │
        │  _core.cpython-     │
        │  312-x86_64-        │
        │  linux-gnu.so       │
        └─────────────────────┘
                    │
                    ▼
┌─────────────────────────────────────────────────────────────────────┐
│                    Final Wheel Structure                             │
│                                                                      │
│  physics_1/                                                          │
│  ├── __init__.py          ← from src/physics_1/__init__.py         │
│  ├── __init__.pyi         ← from src/physics_1/__init__.pyi        │
│  ├── example.pyi          ← from src/physics_1/example.pyi         │
│  ├── linalg.pyi           ← from src/physics_1/linalg.pyi          │
│  └── _core.so             ← installed by CMake                     │
│                                                                      │
│  physics_1-0.1.0.dist-info/                                         │
│  ├── METADATA                                                        │
│  ├── WHEEL                                                           │
│  └── ...                                                             │
└─────────────────────────────────────────────────────────────────────┘
```

## Import Chain Diagram

```
User Code:
┌────────────────────────────────────┐
│  import physics_1                  │
│  physics_1.example.add(1, 2)       │
│  physics_1.linalg.Vector2D(1, 2)   │
└────────────────────────────────────┘
            │
            ▼
Python looks for physics_1 package
            │
            ▼
┌────────────────────────────────────────────────────────────┐
│  src/physics_1/__init__.py                                 │
│  ┌────────────────────────────────────────────────────┐    │
│  │ from ._core import __doc__, __version__,           │    │
│  │                    example, linalg                 │    │
│  │                                                    │    │
│  │ __all__ = ["__doc__", "__version__",              │    │
│  │            "example", "linalg"]                   │    │
│  └────────────────────────────────────────────────────┘    │
└────────────────────────────────────────────────────────────┘
            │
            │ (Python imports ._core which is...)
            ▼
┌────────────────────────────────────────────────────────────┐
│  src/physics_1/_core.so  (Compiled C++ Extension)          │
│  ┌────────────────────────────────────────────────────┐    │
│  │  Created by PYBIND11_MODULE(_core, m, ...)        │    │
│  │                                                    │    │
│  │  Contains:                                         │    │
│  │  • _core.example.add                              │    │
│  │  • _core.example.sub                              │    │
│  │  • _core.linalg.Vector2D                          │    │
│  │  • _core.__version__                              │    │
│  │  • _core.__doc__                                  │    │
│  └────────────────────────────────────────────────────┘    │
└────────────────────────────────────────────────────────────┘
            │
            │ (Which was created from...)
            ▼
┌────────────────────────────────────────────────────────────┐
│  src/main.cpp                                              │
│  ┌────────────────────────────────────────────────────┐    │
│  │ PYBIND11_MODULE(_core, m, ...) {                  │    │
│  │     example::init_example(m);                     │    │
│  │     linalg::init_linalg(m);                       │    │
│  │ }                                                 │    │
│  └────────────────────────────────────────────────────┘    │
└────────────────────────────────────────────────────────────┘
            │
            ├─────────────┬─────────────┐
            ▼             ▼             ▼
┌──────────────────┐ ┌──────────────┐ ┌──────────────┐
│ src/example/     │ │ src/linalg/  │ │ inc/         │
│ functions.cpp    │ │ vector.cpp   │ │ *.h headers  │
│                  │ │              │ │              │
│ init_example()   │ │ init_linalg()│ │ Declarations │
│ • add()          │ │ • Vector2D   │ │              │
│ • sub()          │ │              │ │              │
│ • mul()          │ │              │ │              │
└──────────────────┘ └──────────────┘ └──────────────┘
```

## CMake to Python Module Mapping

```
CMakeLists.txt Command                   Python Result
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

python_add_library(_core MODULE ...)    Creates: _core.so
                   ↑
                   │
                   └─ Module name
                      (must match PYBIND11_MODULE)

install(TARGETS _core 
        DESTINATION physics_1)           Installs to:
                    ↑                    site-packages/
                    │                    physics_1/_core.so
                    └─ Package name          ↑
                       (must match           │
                        directory name)      │
                                            │
src/physics_1/__init__.py ──────────────────┘
    from ._core import ...
         ↑
         └─ Must match installed filename
```

## File Organization Flow

```
Source Tree                          Build Output              Installed Package
─────────────────────────────────────────────────────────────────────────────────

pyproject.toml
CMakeLists.txt
                                                               
src/                                                          
├── main.cpp                    ──→  build/              ──→  site-packages/
├── example/                         _core.so                 physics_1/
│   └── functions.cpp                                         ├── _core.so
├── linalg/                                                   ├── __init__.py
│   └── vector.cpp                                            ├── __init__.pyi
└── physics_1/                  ──→  (copied by          ──→  ├── example.pyi
    ├── __init__.py                   scikit-build-core)      └── linalg.pyi
    ├── __init__.pyi
    ├── example.pyi
    └── linalg.pyi

inc/
├── example/
│   └── functions.h             ──→  (headers used at
└── linalg/                          compile time only,
    └── vector.h                     not installed)
```

## Build Process Timeline

```
Time │ Process                     │ Files Involved
━━━━━┿━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┿━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
     │                             │
  1  │ pip install .               │ (user command)
     │                             │
  2  │ pip reads config            │ pyproject.toml
     │                             │
  3  │ pip loads scikit-build-core │ (build backend)
     │                             │
  4  │ scikit-build-core           │ CMakeLists.txt
     │ invokes cmake configure     │ extern/pybind11/
     │                             │
  5  │ CMake generates Makefiles   │ → build/Makefile
     │                             │
  6  │ scikit-build-core           │ src/main.cpp
     │ invokes cmake build         │ src/example/functions.cpp
     │                             │ src/linalg/vector.cpp
     │                             │ inc/*.h
     │                             │
  7  │ C++ compiler creates        │ → build/_core.so
     │ object files and links      │
     │                             │
  8  │ CMake install step          │ build/_core.so
     │                             │ → staging/physics_1/_core.so
     │                             │
  9  │ scikit-build-core copies    │ src/physics_1/*.py
     │ Python files                │ src/physics_1/*.pyi
     │                             │ → staging/physics_1/
     │                             │
 10  │ scikit-build-core creates   │ staging/ → dist/*.whl
     │ wheel file                  │
     │                             │
 11  │ pip installs wheel          │ dist/*.whl
     │                             │ → site-packages/physics_1/
```

## Type Stub Generation Flow

```
User runs: make stubs
     │
     ▼
┌─────────────────────────────────────────────────┐
│ python -m pybind11-stubgen --output src         │
│                            physics_1            │
└─────────────────────────────────────────────────┘
     │
     ▼
pybind11-stubgen:
1. Imports physics_1._core (must be installed!)
2. Uses Python introspection to discover:
   • All functions and classes
   • Function signatures
   • Docstrings
3. Generates .pyi files

     │
     ▼
┌─────────────────────────────────────────────────┐
│ Output files created in src/physics_1/          │
│                                                 │
│ __init__.pyi:                                   │
│   __version__: str = '0.1.0'                   │
│   from . import example                        │
│   from . import linalg                         │
│                                                 │
│ example.pyi:                                    │
│   def add(i: SupportsInt, j: SupportsInt)     │
│       -> int: ...                              │
│                                                 │
│ linalg.pyi:                                     │
│   class Vector2D:                              │
│       def __init__(self, x: float, y: float)   │
│           -> None: ...                         │
└─────────────────────────────────────────────────┘
     │
     ▼
These .pyi files are:
• Used by IDEs for autocomplete
• Used by type checkers (mypy, pyright)
• Included in the wheel when you run pip install
• Sometimes need manual editing for accuracy
```

## Naming Consistency Requirements

For the build system to work, these names must be consistent:

```
┌─────────────────────────────────────────────────────────────────────┐
│                      CRITICAL NAME MAPPINGS                          │
└─────────────────────────────────────────────────────────────────────┘

Module Name: "_core"
  ├─ CMakeLists.txt:    python_add_library(_core ...)
  ├─ CMakeLists.txt:    install(TARGETS _core ...)
  ├─ src/main.cpp:      PYBIND11_MODULE(_core, m, ...)
  └─ __init__.py:       from ._core import ...

Package Name: "physics_1"
  ├─ pyproject.toml:    name = "physics_1"
  ├─ CMakeLists.txt:    project(physics_1 ...)
  ├─ CMakeLists.txt:    install(... DESTINATION physics_1)
  └─ Directory:         src/physics_1/

Submodule Names: "example", "linalg"
  ├─ src/main.cpp:      example::init_example(m)
  ├─ functions.cpp:     m.def_submodule("example", ...)
  ├─ vector.cpp:        m.def_submodule("linalg", ...)
  ├─ __init__.py:       from ._core import example, linalg
  └─ Stub files:        example.pyi, linalg.pyi

If ANY of these don't match, imports will break!
```

## Common Build Patterns

### Pattern 1: Adding a New C++ Function

```
Step 1: Write C++ code
  inc/example/functions.h:
    int new_func(int x);
  
  src/example/functions.cpp:
    int new_func(int x) { return x * 2; }

Step 2: Expose to Python
  src/example/functions.cpp:
    void init_example(py::module_ &m) {
      m.def_submodule("example", ...)
        .def("new_func", &example::new_func, py::arg("x"));
    }

Step 3: Rebuild and regenerate stubs
  $ pip install . --force-reinstall
  $ make stubs

Result: Can now use physics_1.example.new_func(5) in Python!
```

### Pattern 2: Adding a New Submodule

```
Step 1: Create C++ implementation
  inc/kinematics/motion.h
  src/kinematics/motion.cpp
    namespace kinematics {
      void init_kinematics(py::module_ &m) {
        m.def_submodule("kinematics", "Kinematics module")
          .def("velocity", ...);
      }
    }

Step 2: Register in main.cpp
  src/main.cpp:
    #include <kinematics/motion.h>
    
    PYBIND11_MODULE(_core, m, ...) {
      example::init_example(m);
      linalg::init_linalg(m);
      kinematics::init_kinematics(m);  // ← Add this
    }

Step 3: Update CMakeLists.txt
  python_add_library(_core MODULE
    src/main.cpp
    src/example/functions.cpp
    src/linalg/vector.cpp
    src/kinematics/motion.cpp  # ← Add this
    WITH_SOABI)

Step 4: Update Python interface
  src/physics_1/__init__.py:
    from ._core import __doc__, __version__, 
                       example, linalg, kinematics  # ← Add
    
    __all__ = [..., "kinematics"]  # ← Add

Step 5: Rebuild and generate stubs
  $ pip install . --force-reinstall
  $ make stubs
  # This creates src/physics_1/kinematics.pyi

Result: physics_1.kinematics.velocity() now available!
```

## Summary

The key to understanding this build system is recognizing the three layers:

1. **Python Layer** (`pyproject.toml`, `__init__.py`): User-facing interface
2. **Build Layer** (`scikit-build-core`): Bridges Python and C++
3. **C++ Layer** (`CMakeLists.txt`, `pybind11`, `.cpp/.h`): Implementation

They communicate through:
- File naming conventions (must match!)
- CMake install directives (determines file placement)
- Python import statements (must match installed files)

When everything aligns, `pip install .` magically compiles C++ and creates a usable Python package!
