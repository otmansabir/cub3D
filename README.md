# cub3D

A minimal 3D raycasting engine inspired by Wolfenstein 3D, written in C. It parses a `.cub` configuration/map file, loads textures, and renders a pseudo-3D view using MiniLibX.

This repository is part of the 42 cursus and focuses on fundamentals like parsing, memory management, event handling, and real‑time rendering.

## Table of Contents
- Overview
- Features
- Repository Layout
- Requirements
- Build
- Run
- .cub File Format
- Controls
- Troubleshooting
- License
- Acknowledgements

## Overview
cub3D implements:
- A 2D map parser and validator for `.cub` files
- A raycasting renderer with textured walls
- Basic player movement and rotation
- Simple color management for floor and ceiling
- Keyboard input handling using MiniLibX

## Features
- Textured walls (N/S/E/W)
- Floor and ceiling colors
- Windowed rendering with MiniLibX
- Collision against walls
- Configurable map via `.cub` file

Note: Extra features (doors, sprites, minimap, mouse look, etc.) may be part of the bonus version if implemented.

## Repository Layout
At the root of this repository:
- Makefile — build targets for mandatory and (optionally) bonus parts
- Mandatory/ — sources for the mandatory project
- bonus/ — sources for the bonus part (if used)
- xpm/ — XPM texture assets (paths may be referenced by the `.cub` file)

If you’re exploring the code, start with the `Mandatory/` directory.

## Requirements
You’ll need:
- A C compiler (gcc or clang)
- make
- MiniLibX and its system dependencies

Platform specifics:
- Linux (Debian/Ubuntu)
  - sudo apt update
  - sudo apt install -y build-essential libx11-dev libxext-dev libbsd-dev
- macOS
  - xcode-select --install

Note: MiniLibX may be vendored and built by the provided Makefile. If not, ensure it’s installed/available per your environment.

## Build
Common Makefile targets (run at repository root):
- make — build the mandatory target
- make bonus — build the bonus target (if defined)
- make clean — remove object files
- make fclean — remove objects and final binaries
- make re — rebuild from scratch

The exact output binary names are typically `cub3D` (mandatory) and `cub3D_bonus` (bonus), depending on the Makefile.

## Run
Run the program by providing a `.cub` configuration file (map):

- Mandatory:
  - ./cub3D path/to/map.cub
- Bonus (if built):
  - ./cub3D_bonus path/to/map.cub

If you’re unsure where maps are kept, look for a `maps/` or similar folder inside `Mandatory/` or consult the project’s `.cub` examples. Any valid path to a `.cub` file will work.

## .cub File Format
A `.cub` file typically contains:
- Texture paths (XPM files)
  - NO ./path/to/north.xpm
  - SO ./path/to/south.xpm
  - WE ./path/to/west.xpm
  - EA ./path/to/east.xpm
- Colors (RGB)
  - F r,g,b  (floor color, e.g., F 220,100,0)
  - C r,g,b  (ceiling color, e.g., C 225,30,0)
- Map layout (after the configuration lines)
  - Uses characters: `1` (wall), `0` (empty), spaces (padding), and a single player spawn `N`, `S`, `E`, or `W`

Rules and validation (typical for 42 cub3D):
- The map must be closed (no open holes)
- Exactly one player start
- Only allowed characters are present
- All referenced texture files exist and are valid XPM
- Colors are within 0–255 per channel

Example snippet:
```
NO ./xpm/north.xpm
SO ./xpm/south.xpm
WE ./xpm/west.xpm
EA ./xpm/east.xpm
F 220,100,0
C 225,30,0

1111111
1000001
10N0001
1000001
1111111
```

## Controls
Typical key bindings (may vary depending on the implementation):
- Move: W / A / S / D
- Rotate: Left / Right arrows
- Exit: ESC

If keys differ, check the key definitions in the source under `Mandatory/` (and `bonus/`).

## Troubleshooting
- Window doesn’t open
  - Verify MiniLibX is correctly built/linked and X11 libraries are installed (Linux).
- Segmentation fault on launch
  - Ensure your `.cub` file is valid and texture paths exist (e.g., under `xpm/`).
- Colors look wrong
  - Check `F`/`C` lines are in `R,G,B` format with values 0–255.
- Build errors
  - Run `make fclean && make` to rebuild. Confirm your compiler and headers are installed.

## Acknowledgements
- 42 Network and the cub3D subject
- The MiniLibX library
- Wolfenstein 3D for inspiring the raycasting technique

Author: [@otmansabir](https://github.com/otmansabir)
