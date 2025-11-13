#!/usr/bin/env python3
"""Build script for phys project.

This script provides all build and development tasks with support for
subcommands and flags using argparse.
"""

import argparse
import os
import subprocess
import sys
from pathlib import Path
from typing import Optional, List


class Colors:
    """ANSI color codes for terminal output."""
    RED = '\033[0;31m'
    GREEN = '\033[0;32m'
    YELLOW = '\033[1;33m'
    NC = '\033[0m'  # No Color


def print_step(message: str) -> None:
    """Print a step message in green."""
    print(f"{Colors.GREEN}==>{Colors.NC} {message}")


def print_error(message: str) -> None:
    """Print an error message in red."""
    print(f"{Colors.RED}Error:{Colors.NC} {message}", file=sys.stderr)


def print_warning(message: str) -> None:
    """Print a warning message in yellow."""
    print(f"{Colors.YELLOW}Warning:{Colors.NC} {message}")


def run_command(cmd: List[str], cwd: Optional[Path] = None, check: bool = True) -> subprocess.CompletedProcess:
    """Run a command and handle errors."""
    try:
        return subprocess.run(cmd, cwd=cwd, check=check)
    except subprocess.CalledProcessError as e:
        print_error(f"Command failed with exit code {e.returncode}: {' '.join(cmd)}")
        sys.exit(e.returncode)


def cmd_build(args: argparse.Namespace) -> None:
    """Build the project using CMake."""
    print_step("Building project with CMake")
    run_command(["cmake", "-S", ".", "-B", "build", "-GNinja"])
    run_command(["cmake", "--build", "build"])


def cmd_build_container(args: argparse.Namespace) -> None:
    """Build container for the specified platform architecture."""
    platform = args.platform or "x86_64"
    print_step(f"Building container for platform {platform}")
    
    run_command([
        "docker", "build", ".", "-f", "Containerfile", "-t", "phys",
        "--build-arg", f"PLATFORM_ARCH={platform}"
    ])
    
    # Clean up old container if it exists
    subprocess.run(["docker", "container", "rm", "phys-builder"], 
                   stderr=subprocess.DEVNULL, check=False)
    
    run_command(["docker", "create", "--name", "phys-builder", "phys"])
    
    Path("dist").mkdir(exist_ok=True)
    run_command(["docker", "cp", "phys-builder:/app/wheelhouse/.", "dist/"])
    run_command(["docker", "container", "rm", "phys-builder"])


def cmd_bump(args: argparse.Namespace) -> None:
    """Version bump using commitizen."""
    print_step("Bumping version with commitizen")
    run_command(["cz", "bump", "-s"])


def cmd_ci(args: argparse.Namespace) -> None:
    """Run all CI actions."""
    print_step("Running all CI actions")
    cmd_build(args)
    cmd_format(args)
    cmd_lint(args)
    cmd_test(args)


def cmd_clean(args: argparse.Namespace) -> None:
    """Clean the build directory."""
    print_step("Cleaning build directory")
    
    build_dir = Path("build")
    if build_dir.exists():
        run_command(["cmake", "--build", "build", "--target", "clean"])
    
    # Clean ruff cache, ignore errors
    subprocess.run(["ruff", "clean"], stderr=subprocess.DEVNULL, check=False)


def cmd_clean_full(args: argparse.Namespace) -> None:
    """Full clean - remove build directory."""
    print_step("Full clean - removing build directory")
    
    import shutil
    build_dir = Path("build")
    if build_dir.exists():
        shutil.rmtree(build_dir)


def cmd_format(args: argparse.Namespace) -> None:
    """Run formatting tasks."""
    print_step("Formatting code")
    
    # Format C++ files
    result = subprocess.run(
        ["find", "src", "-iname", "*.h", "-o", "-iname", "*.cpp"],
        capture_output=True, text=True, check=True
    )
    
    if result.stdout.strip():
        files = result.stdout.strip().split('\n')
        run_command(["clang-format", "-i"] + files)
    
    # Format Python files, ignore errors
    subprocess.run(["ruff", "format", "src"], stderr=subprocess.DEVNULL, check=False)


def cmd_install(args: argparse.Namespace) -> None:
    """Install the python package."""
    print_step("Installing python package")
    run_command(["pip", "install", ".", "--no-deps", "--force-reinstall", "-v"])


def cmd_lint(args: argparse.Namespace) -> None:
    """Run linting tasks."""
    print_step("Linting code")
    
    run_command([
        "run-clang-tidy", "-p", "build",
        "-header-filter=.*/inc/.*",
        "-exclude-header=.*extern.*",
        "python", "src", "tests"
    ])
    
    # Run ruff check, ignore errors
    subprocess.run(
        ["ruff", "check", "python", "--exclude", "*.pyi"],
        stderr=subprocess.DEVNULL, check=False
    )


def cmd_stubs(args: argparse.Namespace) -> None:
    """Generate python stubs."""
    print_step("Generating python stubs")
    run_command(["pybind11-stubgen", "--output", "python", "phys"])


def cmd_test(args: argparse.Namespace) -> None:
    """Run all tests."""
    print_step("Running all tests")
    cmd_test_cpp(args)
    cmd_test_python(args)


def cmd_test_cpp(args: argparse.Namespace) -> None:
    """Run C++ core unit tests."""
    print_step("Running C++ unit tests")
    
    test_dir = Path("build/tests")
    if not test_dir.exists():
        print_error("Build directory not found. Run 'build' first.")
        sys.exit(1)
    
    run_command(["ctest", "--output-on-failure"], cwd=test_dir)


def cmd_test_python(args: argparse.Namespace) -> None:
    """Run python problem set tests."""
    print_step("Running python tests")
    
    pytest_args = ["python", "-m", "pytest"]
    if args.verbose:
        pytest_args.append("-v")
    
    run_command(pytest_args)


def cmd_wheel(args: argparse.Namespace) -> None:
    """Package as wheel."""
    print_step("Building python wheel")
    run_command(["python", "-m", "build", "--wheel"])


def create_parser() -> argparse.ArgumentParser:
    """Create and configure the argument parser."""
    parser = argparse.ArgumentParser(
        description="Build script for phys project",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s build
  %(prog)s build-container --platform aarch64
  %(prog)s test --verbose
  %(prog)s ci
        """
    )
    
    subparsers = parser.add_subparsers(dest="command", help="Available commands")
    
    # Build command
    parser_build = subparsers.add_parser("build", help="Build the project using CMake")
    parser_build.set_defaults(func=cmd_build)
    
    # Build container command
    parser_build_container = subparsers.add_parser(
        "build-container",
        help="Build container (default: x86_64)"
    )
    parser_build_container.add_argument(
        "--platform", "-p",
        choices=["x86_64", "aarch64"],
        default="x86_64",
        help="Platform architecture (default: x86_64)"
    )
    parser_build_container.set_defaults(func=cmd_build_container)
    
    # Bump command
    parser_bump = subparsers.add_parser("bump", help="Version bump using commitizen")
    parser_bump.set_defaults(func=cmd_bump)
    
    # CI command
    parser_ci = subparsers.add_parser("ci", help="Run all CI actions (build, format, lint, test)")
    parser_ci.set_defaults(func=cmd_ci)
    
    # Clean command
    parser_clean = subparsers.add_parser("clean", help="Clean the build directory")
    parser_clean.set_defaults(func=cmd_clean)
    
    # Clean-full command
    parser_clean_full = subparsers.add_parser(
        "clean-full",
        help="Full clean - remove build directory"
    )
    parser_clean_full.set_defaults(func=cmd_clean_full)
    
    # Format command
    parser_format = subparsers.add_parser("format", help="Run formatting tasks")
    parser_format.set_defaults(func=cmd_format)
    
    # Install command
    parser_install = subparsers.add_parser("install", help="Install the python package")
    parser_install.set_defaults(func=cmd_install)
    
    # Lint command
    parser_lint = subparsers.add_parser("lint", help="Run linting tasks")
    parser_lint.set_defaults(func=cmd_lint)
    
    # Stubs command
    parser_stubs = subparsers.add_parser("stubs", help="Generate python stubs")
    parser_stubs.set_defaults(func=cmd_stubs)
    
    # Test command
    parser_test = subparsers.add_parser("test", help="Run all tests")
    parser_test.add_argument(
        "--verbose", "-v",
        action="store_true",
        help="Verbose output for tests"
    )
    parser_test.set_defaults(func=cmd_test)
    
    # Test-cpp command
    parser_test_cpp = subparsers.add_parser("test-cpp", help="Run C++ core unit tests")
    parser_test_cpp.set_defaults(func=cmd_test_cpp)
    
    # Test-python command
    parser_test_python = subparsers.add_parser("test-python", help="Run python problem set tests")
    parser_test_python.add_argument(
        "--verbose", "-v",
        action="store_true",
        help="Verbose output for tests"
    )
    parser_test_python.set_defaults(func=cmd_test_python)
    
    # Wheel command
    parser_wheel = subparsers.add_parser("wheel", help="Package as wheel")
    parser_wheel.set_defaults(func=cmd_wheel)
    
    return parser


def main() -> None:
    """Main entry point."""
    parser = create_parser()
    args = parser.parse_args()
    
    if not args.command:
        parser.print_help()
        sys.exit(1)
    
    # Execute the command
    args.func(args)


if __name__ == "__main__":
    main()
