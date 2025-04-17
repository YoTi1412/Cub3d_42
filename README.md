# Cub3D - A Raycasting Game Engine

## Overview
Cub3D is a sophisticated raycasting game engine inspired by the revolutionary Wolfenstein 3D game. This project implements a first-person perspective maze renderer using raycasting technology, providing a powerful foundation for 3D game development.

## Technical Implementation

### Raycasting Technique In-Depth
The raycasting engine creates a 3D perspective by casting rays from the player's position and calculating their intersections with walls. Here's a detailed breakdown:

1. **Ray Calculation and Camera Plane**:
   ```
   Player (P) with direction vector (D)
   Camera plane (C) perpendicular to direction
   
        C1 -------- C2  (Camera plane)
         \          /
          \        /
           \      /
            \    /
             \  /
              P→D  (Player & Direction)
   ```
   For each vertical screen column:
   ```c
   // x ranges from 0 to SCREEN_W
   camera_x = 2 * x / (double)SCREEN_W - 1;  // Ranges from -1 to 1
   
   // Calculate ray direction
   raydir_x = dir_x + plane_x * camera_x;    // Combine direction and camera plane
   raydir_y = dir_y + plane_y * camera_x;    // to get the ray direction
   ```

2. **Digital Differential Analysis (DDA) Algorithm**:
   ```
   Map Grid:
   +---+---+---+
   |   |   |   |
   +---+---+---+
   |   | P→ray |
   +---+---+---+
   |   |   |   |
   +---+---+---+
   ```
   The DDA algorithm efficiently finds wall intersections:
   ```c
   // Calculate distance between ray intersections
   delta_dist_x = fabs(1 / raydir_x);
   delta_dist_y = fabs(1 / raydir_y);

   // Initial step and side distance calculation
   if (raydir_x < 0) {
       step_x = -1;
       side_dist_x = (player.pos_x - map_x) * delta_dist_x;
   } else {
       step_x = 1;
       side_dist_x = (map_x + 1.0 - player.pos_x) * delta_dist_x;
   }
   // Similar calculation for Y axis
   ```

3. **Wall Distance Calculation and Fisheye Correction**:
   ```
   Player's View:
          Wall
           |
   Player  | <- Perpendicular distance used
     •     |    (prevents fisheye effect)
      \    |
       \   |
        \  |
         \ |
   ```
   ```c
   // Calculate perpendicular wall distance
   if (side == 0) {  // X-axis wall hit
       perp_wall_dist = (map_x - player.pos_x + (1 - step_x) / 2) / raydir_x;
   } else {          // Y-axis wall hit
       perp_wall_dist = (map_y - player.pos_y + (1 - step_y) / 2) / raydir_y;
   }

   // Calculate wall height on screen
   line_height = (int)(SCREEN_H / perp_wall_dist);
   draw_start = -line_height / 2 + SCREEN_H / 2;
   draw_end = line_height / 2 + SCREEN_H / 2;
   ```

4. **Texture Mapping Process**:
   ```
   Wall Texture:
   +---------------+
   |   (tex_x,0)   |
   |       |       |
   |       |       |
   |       ↓       |
   |   Vertical    |
   |    stripe     |
   |       |       |
   |       |       |
   +---------------+
   ```
   ```c
   // Calculate wall X coordinate where the ray hit
   if (side == 0)
       wall_x = player.pos_y + perp_wall_dist * raydir_y;
   else
       wall_x = player.pos_x + perp_wall_dist * raydir_x;
   wall_x -= floor(wall_x);

   // Calculate texture coordinates
   tex_x = (int)(wall_x * TEXWIDTH);
   if ((side == 0 && raydir_x > 0) || (side == 1 && raydir_y < 0))
       tex_x = TEXWIDTH - tex_x - 1;

   // Calculate texture Y coordinates
   step = 1.0 * TEXHEIGHT / line_height;
   tex_pos = (draw_start - SCREEN_H / 2 + line_height / 2) * step;
   ```

### Advanced Features

1. **Movement System Implementation**:
   ```c
   // Forward/Backward movement (W/S keys)
   if (key == W_KEY)
       new_x = pos_x + dir_x * move_speed;
       new_y = pos_y + dir_y * move_speed;

   // Rotation (Left/Right arrow keys)
   if (key == LEFT_KEY) {
       old_dir_x = dir_x;
       dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
       dir_y = old_dir_x * sin(rot_speed) + dir_y * cos(rot_speed);
       // Update camera plane similarly
   }
   ```

2. **Texture Rendering System**:
   - North/South textures for X-axis collisions
   - East/West textures for Y-axis collisions
   ```c
   t_image *get_texture_directions(t_game *game) {
       if (game->rc.side == 0) {  // X-axis collision
           return (game->rc.raydir_x > 0) ? game->so_img : game->no_img;
       } else {                    // Y-axis collision
           return (game->rc.raydir_y > 0) ? game->ea_img : game->we_img;
       }
   }
   ```

3. **Map Validation and Parsing**:
   - Checks for valid wall enclosure
   - Validates texture paths and color codes
   - Ensures single player starting position
   - Example valid map structure:
   ```
   111111111111
   100000000001
   100000000001
   1000N0000001
   100000000001
   111111111111
   ```

## Map Format Specification

### Texture and Color Configuration
```
// Texture paths (mandatory)
NO ./textures/north_wall.xpm    // North-facing wall texture
SO ./textures/south_wall.xpm    // South-facing wall texture
WE ./textures/west_wall.xpm     // West-facing wall texture
EA ./textures/east_wall.xpm     // East-facing wall texture

// Colors (RGB format, values 0-255)
F 220,100,0    // Floor color
C 225,30,0     // Ceiling color
```

### Map Layout Rules
1. Must be surrounded by walls (1)
2. Valid characters:
   - '1' : Wall
   - '0' : Empty space
   - 'N/S/E/W' : Player starting position and orientation
3. No empty lines within map section
4. Must be rectangular or square

## Installation and Setup

1. **Prerequisites**:
   - MinilibX library
   - X11 development files
   - GCC/Clang compiler
   - Make build system

2. **Building the Project**:
   ```bash
   # Clone the repository
   git clone [repository-url]
   cd cub3d

   # Build the project
   make        # Build mandatory features
   make bonus  # Build with bonus features
   ```

3. **Running the Game**:
   ```bash
   ./cub3D maps/valid/map.cub
   ```

## Controls
- Movement:
  - `W` - Move forward
  - `S` - Move backward
  - `A` - Strafe left
  - `D` - Strafe right
- Camera:
  - `←` - Rotate camera left
  - `→` - Rotate camera right
- System:
  - `ESC` - Exit game

## Performance Optimization Techniques

1. **DDA Algorithm Optimization**:
   - Eliminates need for floating-point multiplication in ray steps
   - Reduces calculations per ray cast
   - Only checks grid cells that are actually hit by the ray

2. **Texture Management**:
   - Pre-loads textures at startup
   - Uses direct memory access for texture pixel retrieval
   - Implements efficient texture coordinate calculation

3. **Memory Management**:
   - Uses static buffers where possible
   - Minimizes memory allocation during rendering
   - Implements efficient pixel drawing routines

4. **Rendering Optimization**:
   - Single buffer rendering
   - Minimizes floating-point operations
   - Efficient wall height calculations

## Error Handling

1. **Map Validation**:
   - Checks for file existence and permissions
   - Validates texture file formats
   - Ensures map is properly enclosed
   - Verifies color values

2. **Runtime Checks**:
   - Memory allocation verification
   - Texture loading validation
   - Window creation checks
   - Input validation

## Requirements
- MinilibX library (graphical interface)
- C compiler (gcc/clang)
- Make build system
- X11 environment
- Standard C libraries
