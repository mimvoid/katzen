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
            raygui
            glm
            catch2_3
          ];

          shellHook = ''
            export CMAKE_PREFIX_PATH="${pkgs.raygui}"
          '';
        };
      });
    };
}
