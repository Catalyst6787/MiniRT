# shell.nix
{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.pkg-config
    pkgs.xorg.libX11
    pkgs.xorg.libXext
    pkgs.binutils
    pkgs.libbsd
  ];

  shellHook = ''
    export PKG_CONFIG_PATH="${pkgs.xorg.libX11}/lib/pkgconfig"
    fish
  '';
}

