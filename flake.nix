{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {self, nixpkgs, utils}:
    let
      out = system:
    let
      pkgs = nixpkgs.legacyPackages."${system}";
    in {
      defaultPackage = mkDerivation {
        name = "dwm";
        src = ./.;
      };
    }; in with utils.lib; eachSystem defaultSystem out;
}
