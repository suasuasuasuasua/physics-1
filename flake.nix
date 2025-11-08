# Nix flake for the phys Python package
#
# This flake provides:
# - A Python package derivation (buildPythonPackage) that builds the C++ backend
#   with pybind11 bindings
# - A development shell with all build and development dependencies
#
# Usage:
#   nix build           - Build the package
#   nix develop         - Enter development shell
#   nix profile install - Install to your profile
#
# The package uses scikit-build-core to build C++ extensions with CMake.
# Git submodules (pybind11 and googletest) are populated from nixpkgs.
{
  description = "A physics learning project with C++ backend and Python bindings";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        
        # Using Python 3.13 to match the project's development environment
        # The project requires Python >= 3.11, but 3.13 is used in devenv.nix
        python = pkgs.python313;
        pythonPackages = python.pkgs;

        phys = pythonPackages.buildPythonPackage {
          pname = "phys";
          version = "1.0.6";
          format = "pyproject";

          src = ./.;

          nativeBuildInputs = with pkgs; [
            cmake
            ninja
            pythonPackages.scikit-build-core
            pythonPackages.pybind11
          ];

          buildInputs = with pkgs; [
            pythonPackages.pybind11
          ];

          propagatedBuildInputs = with pythonPackages; [
            numpy
          ];

          # Disable checks during build
          dontUseCmakeConfigure = true;
          doCheck = false;

          # Handle git submodules by using packages from nixpkgs
          postUnpack = ''
            # Ensure extern directories exist and populate them with nixpkgs versions
            cd $sourceRoot
            mkdir -p extern/pybind11
            mkdir -p extern/googletest
            
            # Use pybind11 from nixpkgs if not already present
            if [ ! -f extern/pybind11/CMakeLists.txt ]; then
              echo "Populating pybind11 from nixpkgs..."
              cp -r ${pythonPackages.pybind11.src}/* extern/pybind11/
              chmod -R u+w extern/pybind11
            fi
            
            # Use googletest from nixpkgs if not already present
            if [ ! -f extern/googletest/CMakeLists.txt ]; then
              echo "Populating googletest from nixpkgs..."
              cp -r ${pkgs.gtest.src}/* extern/googletest/
              chmod -R u+w extern/googletest
            fi
          '';

          meta = with pkgs.lib; {
            description = "A repository dedicated to learning physics from the ground up";
            homepage = "https://github.com/suasuasuasuasua/phys";
            license = licenses.unfree; # Update with actual license if available
            maintainers = [ ];
            platforms = platforms.unix;
          };
        };

      in
      {
        packages = {
          default = phys;
          phys = phys;
        };

        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            # Build tools
            cmake
            ninja
            git
            
            # C++ development
            gcc
            clang-tools
            
            # Python and dependencies
            python
            pythonPackages.pip
            pythonPackages.numpy
            pythonPackages.scikit-build-core
            pythonPackages.pybind11
            pythonPackages.pybind11-stubgen
            pythonPackages.build
            
            # Development tools
            pythonPackages.pytest
            pythonPackages.ruff
            pythonPackages.ipython
            pythonPackages.commitizen
          ];

          shellHook = ''
            echo "Physics project development environment"
            echo "Python version: $(python --version)"
            echo "CMake version: $(cmake --version | head -n1)"
            echo ""
            echo "Available commands:"
            echo "  ninja build    - Build the project"
            echo "  ninja install  - Install the Python package"
            echo "  ninja test     - Run tests"
            echo "  ninja ci       - Run all CI actions"
          '';
        };
      }
    );
}
