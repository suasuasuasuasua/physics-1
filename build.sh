#!/usr/bin/env bash
# Build script for phys project
# This script replaces the ninja build system with bash functions

set -e  # Exit on error

# Color output for better readability
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Helper function to print messages
print_step() {
    echo -e "${GREEN}==>${NC} $1"
}

print_error() {
    echo -e "${RED}Error:${NC} $1" >&2
}

print_warning() {
    echo -e "${YELLOW}Warning:${NC} $1"
}

# Build the project using CMake
build() {
    print_step "Building project with CMake"
    cmake -S . -B build -GNinja
    cmake --build build
}

# Build container for the specified platform architecture
# Usage: ./build.sh build-container [PLATFORM_ARCH]
# Example: ./build.sh build-container aarch64
build_container() {
    local platform="${1:-x86_64}"
    print_step "Building container for platform ${platform}"
    docker build . -f Containerfile -t phys --build-arg PLATFORM_ARCH="${platform}"
    docker container rm phys-builder 2>/dev/null || true
    docker create --name phys-builder phys
    mkdir -p dist
    docker cp phys-builder:/app/wheelhouse/. dist/
    docker container rm phys-builder
}

# Version bump using commitizen
bump() {
    print_step "Bumping version with commitizen"
    cz bump -s
}

# Run all CI actions
ci() {
    print_step "Running all CI actions"
    build
    format
    lint
    test
}

# Clean the build directory
clean() {
    print_step "Cleaning build directory"
    if [ -d build ]; then
        cmake --build build --target clean
    fi
    ruff clean 2>/dev/null || true
}

# Full clean - remove build directory
clean_full() {
    print_step "Full clean - removing build directory"
    rm -rf build/
}

# Run formatting tasks
format() {
    print_step "Formatting code"
    find src -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i
    ruff format src 2>/dev/null || true
}

# Install the python package
install() {
    print_step "Installing python package"
    pip install . --no-deps --force-reinstall -v
}

# Run linting tasks
lint() {
    print_step "Linting code"
    run-clang-tidy -p build -header-filter=".*/inc/.*" -exclude-header=".*extern.*" python src tests
    ruff check python --exclude "*.pyi" 2>/dev/null || true
}

# Generate python stubs
stubs() {
    print_step "Generating python stubs"
    pybind11-stubgen --output python phys
}

# Run all tests
test() {
    print_step "Running all tests"
    test_cpp
    test_python
}

# Run C++ core unit tests
test_cpp() {
    print_step "Running C++ unit tests"
    if [ -d build/tests ]; then
        cd build/tests
        ctest --output-on-failure
        cd ../..
    else
        print_error "Build directory not found. Run './build.sh build' first."
        exit 1
    fi
}

# Run python problem set tests
test_python() {
    print_step "Running python tests"
    python -m pytest -v
}

# Package as wheel
wheel() {
    print_step "Building python wheel"
    python -m build --wheel
}

# Show help message
help() {
    cat << EOF
Usage: ./build.sh [command] [args]

Available commands:
  build              Build the project using CMake
  build-container    Build container (default: x86_64, or pass arch as arg)
  bump               Version bump using commitizen
  ci                 Run all CI actions (build, format, lint, test)
  clean              Clean the build directory
  clean-full         Full clean - remove build directory
  format             Run formatting tasks
  install            Install the python package
  lint               Run linting tasks
  stubs              Generate python stubs
  test               Run all tests
  test-cpp           Run C++ core unit tests
  test-python        Run python problem set tests
  wheel              Package as wheel
  help               Show this help message

Examples:
  ./build.sh build
  ./build.sh build-container aarch64
  ./build.sh test
  ./build.sh ci

EOF
}

# Main entry point
main() {
    local command="${1:-build}"
    shift || true
    
    case "$command" in
        build)
            build "$@"
            ;;
        build-container)
            build_container "$@"
            ;;
        bump)
            bump "$@"
            ;;
        ci)
            ci "$@"
            ;;
        clean)
            clean "$@"
            ;;
        clean-full)
            clean_full "$@"
            ;;
        format)
            format "$@"
            ;;
        install)
            install "$@"
            ;;
        lint)
            lint "$@"
            ;;
        stubs)
            stubs "$@"
            ;;
        test)
            test "$@"
            ;;
        test-cpp)
            test_cpp "$@"
            ;;
        test-python)
            test_python "$@"
            ;;
        wheel)
            wheel "$@"
            ;;
        help|--help|-h)
            help
            ;;
        *)
            print_error "Unknown command: $command"
            echo ""
            help
            exit 1
            ;;
    esac
}

# Run main if script is executed directly
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    main "$@"
fi
