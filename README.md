# Cub3D &nbsp;![language](https://img.shields.io/badge/language-444444?logo=c&labelColor=555555) ![makefile](https://img.shields.io/badge/make-444444?logo=monster&logoColor=goldenrod&labelColor=555555) ![42](https://img.shields.io/badge/school-444444?logo=42&logoColor=black&labelColor=777777&link=https%3A%2F%2Fwww.42lisboa.com%2Fpt%2F)

*This project has been created as part of the 42 curriculum by lbraga & vpinto-g.*

**Cub3D** is a practical implementation of a dynamic 3D graphical engine in C using the **miniLibX** library, inspired by the iconic 1992 game *Wolfenstein 3D*. The project explores the fundamentals of real-time 2D-to-3D computer graphics through **Raycasting**—a rendering technique that projects a 3D perspective from a 2D grid-based map environment while keeping track of precise player mechanics, textures, and event hooks.

1. [Overview](#overview)
2. [Algorithm](#algorithm)
3. [Data Structures](#data-structures)
4. [Instructions](#instructions)
5. [Resources](#resources)
6. [AI Disclosure](#ai-disclosure)
7. [Final Notes](#final-notes)

## Overview

The engine processes a scene description file `.cub` to validate map boundaries, loads wall textures, parses floor/ceiling RGB colors, and renders a simulated 3D environment in real-time. The goal is to provide a seamless interactive experience with fluid player locomotion, camera rotations, and a clean event-driven exit pipeline.

### Scene Validation & Configuration

All map configurations and parameters are validated prior to starting the graphical interface. The program enforces strict validation rules and recommendations:

```bash
./cub3D maps/subject.cub
```

- **Scene Identifiers**: Texture paths for wall orientations `NO`, `SO`, `WE`, `EA` and floor/ceiling colors (`F`, `C`) must be uniquely defined before the map content.
- **Color Format**: RGB values must fall strictly within the standard integer range `[0, 255]`.
- **Enclosure Check**: The playable space `0` and player starting positions `N`/`S`/`E`/`W`) must be completely enclosed by wall tiles `1`. Any access to open space or void results in an immediate parsing error.
- **Player Spawning**: Exactly one player spawn indicator (`N`, `S`, `E`, or `W`) must exist within the grid, defining both the initial coordinates and the starting camera angle.

## Algorithm

The rendering pipeline relies on **Raycasting** powered by the **Digital Differential Analyzer (DDA)** grid traversal algorithm.

### Rendering Mechanics

- **Ray Generation**: Rays are cast horizontally across screen pixels. The camera plane is calibrated to maintain an FOV aspect ratio matching, calculating distinct ray direction vectors across the viewing plane.
- **DDA Grid Traversal**: Rather than advancing ray vectors by small arbitrary increments, the DDA algorithm calculates exact intersection points across grid boundaries $X$ and $Y$ steps until it hits a wall `1`:
  - **Delta Distance (`deltaDistX` / `deltaDistY`)**: Distance the ray travels to jump from one grid line to the next.
  - **Side Distance (`sideDistX` / `sideDistY`)**: Initial distance from player position to the first grid boundary.
- **Fisheye Correction & Projection**: Perpendicular wall distance `perpWallDist` is derived instead of Euclidean distance to eliminate the fisheye effect. The slice wall height is calculated inversely proportional to this distance and projected onto screen height buffers.
- **Texture Mapping & Compiler Optimization**: Wall hit coordinates determine texture `offset_x`, stepping along the texture image buffer to stretch wall strips cleanly. The core rendering routine is optimized using the `-O2` compilation flag to ensure steady frame rates during intensive screen redrawing.

### Minimap System

A dynamic Wolfenstein 3D-style overlay HUD provides an real-time top-down 2D radar view of the surrounding map layout.

- **Pixel Coordinate Transformation**: Converts 2D world coordinates into screen-space pixel blocks on the HUD overlay buffer.

- **Toggleable Flat FOV Mode (`g->input.show_flat`)**: Provides two dynamic display modes for performance and clarity:
  - **Cone Vision Mode**: Renders 2 boundary FOV edge rays to represent player vision field with minimum CPU overhead.
  - **Full FOV Sweep Mode**: Casts every ray across the active FOV span directly onto the 2D grid HUD for a detailed radar visualization.

## Data Structures

The application relies on dedicated structures to handle configuration setup, player physics, DDA calculations, texture buffers, and key inputs.

#### 1. Global Game Context (`t_game`)
Acts as the central context holding MiniLibX handlers, image buffers, scene setup, loaded wall textures, player state, and key inputs.
```c
typedef struct s_game
{
	void		*mlx;		// MiniLibX pointer
	void		*win;		// Window pointer
	void		*img;		// Image buffer pointer
	char		*data;		// Pixel data pointer
	int		bpp;		// Bits per pixel
	int		size_line;	// Image line size
	int		endian;		// Endianness format
	char		**map;		// 2D grid map 
	int		tile;		// Map tile size
	t_setup		setup;		// Parsed configuration
	t_texture	texture[4];	// Loaded textures [NO, SO, WE, EA]
	t_input		input;		// Keyboard input states
	t_player	player;		// Player structure
}	 t_game;
```

#### 2. Scene Configuration (`t_setup`)
Holds raw configuration values extracted from the `.cub` scene file prior to graphic initialization.
```c
typedef struct s_setup
{
	char	**map;		// Parsed 2D grid map 
	int	color_c;	// RGB ceiling color
	int	color_f;	// RGB floor color
	char	dir;		// Direction 'N', 'S', 'E', 'W'
	int	pos_x;		// Player position X
	int	pos_y;		// Player position X
	char	*tex_n;		// Path North texture
	char	*tex_s;		// Path South texture
	char	*tex_e;		// Path East texture
	char	*tex_w;		// Path West texture
}   t_setup;
```

#### 3. Player State (`t_player`)
Tracks high-precision position coordinates, orientation direction vectors, and camera plane properties.
```c
typedef struct s_player
{
	double  pos_x;		// Float position X 
	double  pos_y;		// Float position y
	double  fov_factor;	// FOV scaling factor
	double  pln_x;		// Camera plane X
	double  pln_y;		// Camera plane Y
	double  dir;		// Player Direction
	double  dir_x;		// Direction X
	double  dir_y;		// Direction Y
}   t_player;
```

#### 4. DDA Computation context (`t_dda`)
Contains variables generated during ray step calculation and wall projection.
```c
typedef struct s_dda
{
	double	cam_x;		// X camera (-1 to 1)
	double	cam_step;	// Camera step
	int	map_x;		// Map position X
	int	map_y;		// Map position Y
	double	dir_x;		// Ray direction X
	double	dir_y;		// Ray direction Y
	double	delta_x;	// Ray distance X lines
	double	delta_y;	// Ray distance Y lines
	int	step_x;		// Step direction X
	int	step_y;		// Step direction Y
	double	dist_x;		// Distance to next X line
	double	dist_y;		// Distance to next Y line
	int	side_hit;	// Axis hit indicator
	double	perp_dist;	// Perpendicular distance
	double	offset_x;	// Wall hit X ratio 
	int	index;		// Texture indication
	int	x;			// Screen X
	double	height;		// Screen pixel height
	int	start;		// Screen start pixel Y
	int	end;		// Screen end pixel Y
}   t_dda;
```

#### 5. Additional Subsystem Structures
Structures managing texture image buffers, input states, minimap calculations, and rasterization lines.

- **`t_texture`** : Stores the MLX image pointer, dimensions, and pixel memory metadata (data, bpp, size_line, endian) for each wall direction to allow direct pixel manipulation when rendering textures.

- **`t_input`** : Holds boolean flags for all active movement keys and minimap view modes to ensure smooth, non-blocking frame updates.

- **`t_tile`** : Handles map dimension calculations, pixel rendering sizes, and tile scale factors used to position and draw the minimap grid accurately on screen.

- **`t_line`** : Encapsulates screen coordinates ($X, Y$), line lengths, and termination end points to draw vertical walls and minimap elements.


## Instructions

To build the program, you need `cc`, `make`, `X11`  and standard thread libraries installed.

1. Clone the repository:
	```bash
	git clone https://github.com/leandrobbj/cub3D.git && cd cub3D
	```

2. Clone minilibx:
	```bash
	git clone https://github.com/42paris/minilibx-linux.git
	```

2. Build the program:
	```bash
	make
	```
<p align="right"> <i>*In newer complilers use make new</i>

3. Launch the engine with a map:
	```bash
	./cub3D maps/subject.cub
	```

### Make Targets

- `make` builds `cub3D`.
- `make clean` removes compiled object files.
- `make fclean` removes object files and the `cub3D` binary.
- `make re` runs `fclean` followed by `make`.
- `make new` builds `cub3D` in newer compilers.

### Keybindings

| Key / Input | Action |
| :--- | :--- |
| `W` / `Up`| Move forward |
| `S`/ `Down` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `Left` | Rotate view left |
| `Right` | Rotate view right |
| `M` | Toggle Minimap|
| `F` | Toggle render flat|
| `Shift` | Run |
| `Esc` | Safely close window and exit |

### Scene File Structure (`.cub`)

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111111111
1000000000001
1011000001001
1001000000N01
1111111111111
```

### Additional Configuration
Structures managing texture image buffers, input states, minimap calculations, and rasterization lines.

- **Window Resolution**: Adjust the rendering screen dimensions to fit your preferred display format.
- **FOV**: Modify the camera's field of view angle to control the width and perspective distortion of the 3D raycasting projection.
- **Speeds**: Tweak movement multipliers for player displacement, strafing, and keyboard or mouse rotation responsiveness.
- **Map**: Configure the screen percentage to customize the size and scale of the minimap.
- **Margin**: Define the collision buffer distance to prevent the player's position from clipping directly into walls.
- **Colors**: Use `TILE1` and `TILE2` to customize the distinct colors for the minimap, and `WALL1` and `WALL2` to customize the wall colors in flat mode.

## Resources

- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) - Depth breakdown of vector math, camera planes, and DDA mechanics.
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Comprehensive guide on MLX windows, hooks, images, and loop handling.
- [X11 Event Specifications](https://tronche.com/gui/x/xlib/events/) - Reference for keypress, keyrelease, and destroy notification event masks.

## AI Disclosure

In accordance with the 42 curriculum guidelines, AI tools were utilized during the architectural planning phase to analyze vector rotation matrices, verify DDA step edge cases, optimize top-down HUD minimap drawing performance, design leak-free cleanup handlers for MiniLibX DestroyNotify hooks, and format this structured documentation.

## Final Notes

Working on cub3D was a dive into the math and logic behind early 3D graphics engines. It transformed raw matrix transformations, trigonometry, and pixel manipulation into something visually interactive. Figuring out how to draw textured walls without lag, manage key states smoothly, and parse custom map layouts brought back the appreciation for how developers in the 90s squeezed incredible performance out of limited hardware.