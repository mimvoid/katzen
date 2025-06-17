{
  description = "Flake for katzen";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs = { self, nixpkgs }:
    let
      allSystems = nixpkgs.lib.genAttrs nixpkgs.lib.platforms.all;

      toSystems = passPkgs: allSystems (system:
        passPkgs (import nixpkgs { inherit system; })
      );
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

          buildInputs = [
            pkgs.raylib
            pkgs.glm
          ];
        };
      });

      devShells = toSystems (pkgs: {
        default = pkgs.mkShell {
          packages = with pkgs; [
            # C++
            libcxx
            libcxxrt

            # Development tools
            clang
            clang-tools
            cmake
            ninja

            # Libraries
            (raylib.override { platform = "SDL"; })
            glm
            catch2_3
          ];

          shellHook = ''
            export CC=${pkgs.clang}/bin/clang
            export CXX=${pkgs.clang}/bin/clang++
          '';
        };
      });
    };
}
