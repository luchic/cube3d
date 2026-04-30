# cub3D

Small 3D maze renderer in C using **MLX42** and **raycasting**.
The goal is to recreate a Wolfenstein-like first-person view from a `.cub` map file.

## Project Features

- Parse a `.cub` scene file with extensive error handling
- Load wall textures (PNG format via MLX42) and floor/ceiling colors
- Render a 3D view of the maze using raycasting
- Real-time movement and rotation
- Minimap with player orientation
- Texture mapping for walls based on cardinal directions
- Screen-buffer rendering for smooth performance

## Technical Details

- Language: `C`
- Graphics: `MLX42`
- Input: map file in `.cub` format
- Walls use different textures: `NO`, `SO`, `WE`, `EA`
- Map must be valid, closed by walls, and contain exactly one starting position

## Project Structure

```text
.
├── Makefile                # Build system
├── include/                # Header files
│   ├── cub3d.h             # Main app header
│   └── defs.h              # Structs and definitions
├── libft/                  # Custom C library
├── mlx42/                  # MLX42 graphics library
├── srcs/                   # Source files
│   ├── main.c              # Entry point
│   ├── mlx/                # MLX42 initialization and hooks
│   ├── parsing/            # .cub file parsing and validation
│   ├── player/             # Player state and movement
│   ├── render/             # Raycasting and frame drawing
│   └── tools/              # Error handling and utilities
├── assets/                 # Game assets
    ├── maps/               # .cub map files
    └── textures/           # PNG texture files

```

## Compilation & Usage

### Prerequisites

- `cmake` (for MLX42)
- `glfw` (for MLX42)
- `gcc` or `clang`

### Build

```bash
make
```

### Run

```bash
./cub3D assets/maps/valid/test.cub
```

## Controls

- `W` / `A` / `S` / `D`: Move player
- `Left` / `Right` arrows: Rotate camera
- `ESC`: Exit program
- Window Close: Exit program

## Authors

- sruff
- nluchini
