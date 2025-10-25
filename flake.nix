{
  description = "Flake for katzen";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs = { self, nixpkgs }:
    let
      allSystems = nixpkgs.lib.genAttrs nixpkgs.lib.platforms.all;
      toSystems = passPkgs: allSystems (system: passPkgs (import nixpkgs { inherit system; }));
    in
    {
      packages = toSystems (pkgs: {
        default = pkgs.stdenv.mkDerivation rec {
          pname = "katzen";
          version = "0.1.0";

          src = builtins.path {
            name = "${pname}-${version}";
            path = pkgs.lib.cleanSource ./.;
          };

          nativeBuildInputs = [
            pkgs.cmake
            pkgs.ninja
          ];

          buildInputs = [ pkgs.raylib ];
        };
      });

      devShells = toSystems (pkgs: {
        default = pkgs.mkShellNoCC {
          name = "katzen";

          nativeBuildInputs = [
            pkgs.clang
          ];

          packages = with pkgs; [
            # C++
            libcxx
            libcxxrt

            # Development tools
            clang-tools
            cmake
            ninja

            # Libraries
            (pkgs.raylib.override { platform = "SDL"; })
            pkgs.catch2_3
          ];
        };
      });
    };
}
