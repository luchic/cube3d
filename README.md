# cub3D

Small 3D maze renderer in C using **MiniLibX** and **raycasting**.
The goal is to recreate a Wolfenstein-like first-person view from a `.cub` map file.

## Project Point

- Parse a `.cub` scene file
- Load wall textures and floor / ceiling colors
- Render a 3D view of the maze with raycasting
- Move the player with `W A S D`
- Rotate the camera with left / right arrows
- Exit cleanly with `ESC` or window close

## Mandatory Idea

- Language: `C`
- Graphics: `MiniLibX`
- Input: map file in `.cub` format
- Walls must use different textures by direction: `NO`, `SO`, `WE`, `EA`
- Map must be valid and closed by walls
- Program should handle errors and free memory correctly

## Suggested Structure

```text
.
├── Makefile
├── README.md
├── include/
│   ├── cub3d.h
│   ├── structs.h
│   └── keys.h
├── src/
│   ├── main.c
│   ├── init/
│   ├── parse/
│   ├── render/
│   ├── player/
│   ├── events/
│   ├── utils/
│   └── cleanup/
├── assets/
│   ├── textures/
│   └── maps/
└── libft/
```

## Architecture Suggestion

- `parse/`: read and validate the `.cub` file
- `init/`: create MLX window, images, textures, and game state
- `render/`: raycasting, wall drawing, floor and ceiling rendering
- `player/`: movement, rotation, collision checks
- `events/`: keyboard input and window hooks
- `cleanup/`: free textures, map, images, and exit safely

## Run

```bash
make
./cub3D assets/maps/map.cub
```

## Bonus Ideas

- Minimap
- Wall collision improvements
- Doors
- Mouse rotation
- Animated sprites
