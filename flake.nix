{
  description = "Network infrastructure docs";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05-small";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
        in
        with pkgs;
        {
        packages.website = pkgs.stdenv.mkDerivation {
          name = "docs";
          src = self;
          buildPhase = "${pkgs.hugo}/bin/hugo";
          installPhase = "cp -r public $out";
        };
        defaultPackage = self.packages.${system}.website;
          devShells.default = mkShell {
            buildInputs = [ hugo ];
          };
        }
      );
}
