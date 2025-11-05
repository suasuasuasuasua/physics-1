{ pkgs, ... }:

{
  # https://devenv.sh/packages/
  packages = [ pkgs.git pkgs.ninja pkgs.commitizen ];

  # https://devenv.sh/languages/
  languages = {
    cplusplus.enable = true;
    python = {
      enable = true;
      venv.enable = true;
      version = "3.13";
    };
    typst.enable = true;
  };

  # disable automatic cache management
  cachix.enable = false;

  # https://devenv.sh/git-hooks/
  git-hooks.hooks = {
    clang-format.enable = true;
    clang-tidy.enable = true;
    cmake-format.enable = true;
    ruff.enable = true;
    ruff-format.enable = true;
    shellcheck.enable = true;
  };

  # See full reference at https://devenv.sh/reference/options/
}
