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

### Using Nix Flakes

This project can be built and distributed as a Nix package using flakes:

```bash
# Build the package
nix build

# Install the package to your profile
nix profile install .

# Enter a development shell with all dependencies
nix develop

# Run the package directly without installing
nix run

# Update flake dependencies
nix flake update
```

#### Using the Built Package

After building with `nix build`, you can use the package in several ways:

**Option 1: Use the result symlink directly**
```bash
# The build creates a 'result' symlink to the package in the Nix store
# You can use Python from the result:
nix build
export PYTHONPATH="$(pwd)/result/lib/python3.13/site-packages:$PYTHONPATH"
python3 -c "import phys; print(phys)"
```

**Option 2: Install to your profile and use it**
```bash
# Install the package to your user profile
nix profile install .

# Now you can import phys in any Python session
python3 -c "import phys"
```

**Option 3: Use nix-shell with the package**
```bash
# Create a temporary shell with the package available
nix shell . -c python3 -c "import phys; print(phys)"
```

**Option 4: Use in a Python environment**
```nix
# In your own flake.nix or shell.nix:
let
  phys = builtins.getFlake "github:suasuasuasuasua/phys";
  pythonEnv = pkgs.python313.withPackages (ps: [
    phys.packages.${pkgs.system}.default
  ]);
in pkgs.mkShell {
  buildInputs = [ pythonEnv ];
}
```

**Option 5: Development workflow**
```bash
# For development, use nix develop which provides all build tools
nix develop
# Inside the dev shell, use the existing ninja commands:
ninja build && ninja install
python3 -c "import phys"
```

> **Note:** The `flake.lock` file will be automatically generated on first use
> to pin dependency versions for reproducibility. Commit this file to version
> control.

The flake provides:
- A derivation for the Python package with all C++ dependencies
- A development shell with build tools, Python, and development dependencies
- Automatic handling of git submodules (pybind11 and googletest)

#### Using in other Nix configurations

You can add this package to your NixOS configuration or home-manager:

```nix
{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    phys.url = "github:suasuasuasuasua/phys";
  };

  outputs = { self, nixpkgs, phys }: {
    # For NixOS system configuration
    nixosConfigurations.mySystem = nixpkgs.lib.nixosSystem {
      system = "x86_64-linux";
      modules = [
        ({ pkgs, ... }: {
          environment.systemPackages = [ phys.packages.${pkgs.system}.default ];
        })
      ];
    };
  };
}
```

Or use it in a shell.nix:

```nix
let
  phys = builtins.getFlake "github:suasuasuasuasua/phys";
in
  pkgs.mkShell {
    buildInputs = [ phys.packages.${pkgs.system}.default ];
  }
```

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
