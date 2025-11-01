# Documentation

Welcome to the physics_1 build system documentation! This directory contains comprehensive guides explaining how the Python/C++ hybrid build system works.

## Documents

### [Build Architecture](build-architecture.md)
**Start here!** A comprehensive explanation of how the build system works, covering:
- Overview of the build system components
- Detailed explanation of `pyproject.toml`, `CMakeLists.txt`, and pybind11
- How scikit-build-core connects Python packaging with CMake
- Package structure and why it must be organized the way it is
- The role of stub files (`.pyi`) and how they're generated
- Common build operations

**Best for:** Understanding the big picture and how all pieces fit together

### [Build Flow Diagrams](build-flow-diagrams.md)
Visual representations and diagrams showing:
- Component relationships
- Import chain flow
- CMake to Python module mapping
- File organization during the build
- Build process timeline
- Type stub generation flow
- Naming consistency requirements
- Common build patterns

**Best for:** Visual learners and quick reference

### [FAQ and Troubleshooting](faq-and-troubleshooting.md)
Common questions and solutions:
- Frequently asked questions about the build system
- Why things are designed the way they are
- Troubleshooting common build and import errors
- Best practices for development workflow
- Debugging tips for C++ code called from Python

**Best for:** Solving specific problems and learning best practices

## Quick Links

### I want to...

- **Understand how `pip install .` compiles my C++ code**
  → Read [Build Architecture - Build Flow](build-architecture.md#build-flow)

- **See a visual representation of the build process**
  → Read [Build Flow Diagrams - Component Relationship](build-flow-diagrams.md#component-relationship-diagram)

- **Add a new C++ function and expose it to Python**
  → Read [Build Flow Diagrams - Common Build Patterns](build-flow-diagrams.md#common-build-patterns)

- **Fix import errors**
  → Read [FAQ - Troubleshooting](faq-and-troubleshooting.md#troubleshooting)

- **Understand why stub files (.pyi) are needed**
  → Read [Build Architecture - Stub Files](build-architecture.md#stub-files-pyi)

- **Learn why the directory structure is so specific**
  → Read [Build Architecture - Package Structure](build-architecture.md#package-structure)

## Key Concepts

The build system connects three worlds:

1. **Python Packaging** (`pyproject.toml`) - Defines package metadata and tells pip how to build
2. **Build Orchestration** (`scikit-build-core`) - Bridges Python and C++ worlds
3. **C++ Compilation** (`CMakeLists.txt` + `pybind11`) - Compiles code and creates Python modules

The "magic" happens because:
- `pyproject.toml` tells pip to use scikit-build-core as the build backend
- scikit-build-core invokes CMake to compile your C++ code
- CMake creates a shared library (`.so` file) that Python can import
- pybind11 makes C++ functions callable from Python
- Everything is packaged into a wheel that pip can install

## Development Workflow

```bash
# 1. Initial setup
git submodule update --init --recursive
pip install -e .

# 2. Make changes to C++ code
vim src/example/functions.cpp

# 3. Rebuild and reinstall
pip install -e . --force-reinstall --no-deps

# 4. Test your changes
python -c "import physics_1; physics_1.example.add(1, 2)"

# 5. Regenerate type stubs (if API changed)
make stubs

# 6. Run tests
make test
```

## Getting Help

If you're stuck:
1. Check the [FAQ](faq-and-troubleshooting.md#frequently-asked-questions)
2. Look at the [Troubleshooting](faq-and-troubleshooting.md#troubleshooting) section
3. Review the [Build Flow Diagrams](build-flow-diagrams.md) for visual explanations
4. Read the detailed [Build Architecture](build-architecture.md) documentation

## Contributing

When adding new features:
1. Follow the patterns in [Build Flow Diagrams - Common Build Patterns](build-flow-diagrams.md#common-build-patterns)
2. Update these docs if you change the build system
3. Regenerate stubs after API changes
4. Run the full test suite

## External Resources

- [pybind11 Documentation](https://pybind11.readthedocs.io/) - Python/C++ binding library
- [scikit-build-core Documentation](https://scikit-build-core.readthedocs.io/) - Build system
- [CMake Documentation](https://cmake.org/documentation/) - C++ build tool
- [Python Packaging Guide](https://packaging.python.org/) - Python packaging standards
- [pybind11 Example Project](https://github.com/pybind/scikit_build_example) - Reference implementation
