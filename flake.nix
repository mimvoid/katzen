{
  description = "Flake for katze";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs =
    { self, nixpkgs }:
    let
      allSystems = nixpkgs.lib.genAttrs nixpkgs.lib.platforms.all;
      toSystems = passPkgs: allSystems (system: passPkgs (import nixpkgs { inherit system; }));
    in
    {
      packages = toSystems (pkgs: {
        default = pkgs.stdenv.mkDerivation rec {
          pname = "katze";
          version = "0.1.0";

          src = builtins.path {
            name = "${pname}-${version}";
            path = pkgs.lib.cleanSource ./.;
          };

          nativeBuildInputs = [
            pkgs.pkg-config
            pkgs.meson
            pkgs.ninja
          ];

          buildInputs = [ pkgs.sdl3 ];
        };
      });

      devShells = toSystems (pkgs: {
        default = pkgs.mkShellNoCC {
          name = "katze";

          nativeBuildInputs = [
            pkgs.pkg-config
            pkgs.clang
          ];

          packages = with pkgs; [
            clang-tools
            ninja
            meson

            sdl3
            sdl3-ttf
            doctest
          ];
        };
      });
    };
}
