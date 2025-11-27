# 𝐒𝟎𝐋𝐈𝐃∆𝐍𝐆𝐋𝐄 - cub3D
cub3D is a 3D graphical project from the 42 curriculum. The goal is to create a basic 3D game engine using raycasting, inspired by early games like Wolfenstein 3D. It uses the MiniLibX graphics library to render a 3D view from a 2D map, allowing the player to move around and interact with the environment.


## 📑 Table of Contents
1. [MLX42 library](#mlx42-library)
2. [Explanation of Key Concepts](#explanation-of-keys-concepts)

---

## MLX42 library

MLX42 is a **graphics library** made by 42 Network students as a modern replacement for the original **MiniLibX (mlx)** that was provided by 42 school.

Here’s the breakdown:

### What it is

- **MLX42** is a lightweight C library built on **OpenGL** and **GLFW**.

- It provides a simple API to create a window, handle keyboard/mouse input, and draw images/pixels.

- It’s designed to be cross-platform (Linux, macOS, sometimes Windows with tweaks), unlike the old MiniLibX which had a lot of platform limitations.

### Why it exists

- The original MiniLibX was outdated, buggy, and heavily tied to X11 (Linux) or Quartz (macOS).

- Many students had problems compiling it, especially on modern macOS.

- MLX42 is meant to be easier to install, more reliable, and more flexible.

### What you can do with MLX42

Create a window and render graphics.

Handle events (keyboard, mouse, window resize, close).

Draw pixels, lines, textures, and images.

Use OpenGL under the hood, but without needing to learn OpenGL directly.

### Download MLX42

To download MLX42, visit the following link and follow the instructions:

[MLX42 on GitHub ↗](https://github.com/codam-coding-college/MLX42)

---

## Explanation of Keys Concepts
### 1. Player Start & Camera Orientation
The Map Is Just a 2D Grid
Think of the map like a chess board:
  - Every cell is 1×1 unit in size
  - '1' means solid wall
  - '0' means walkable floor
  - 'N','S','E','W' are temporary markers that only exist to tell you where the player should spawn and which way they look
  - 'D','O','M' are bonus objects like doors/enemies
Nothing is drawn until you decide what to do with this grid.
See the diagram below for a visual explanation of player initialization and camera orientation.
![Player Start & Camera Orientation](tldraw_diagrams/init_data.png)

### 2. Raycasting = Shooting 1 Ray Per Screen Column

Rendering happens like this: for each x column on your screen, you compute a ray direction.

First compute the camera scale:
```c
camerax = 2.0 * x / SCREEN_WIDTH - 1.0;
```
Now blend direction + plane:
```c
raydirx = player.dirx + player.planex * camerax;
raydiry = player.diry + player.planey * camerax;
```

Meaning:

- When camerax = 0 → ray shoots exactly forward

- `>0` → bent right

- `<0` → bent left

- The further from 0, the stronger the plane influence

This is how FOV becomes actual visible rays.

### 3. Preparing DDA (Digital Differential Analyzer)

Now you determine how far a ray travels through 1 tile in X or Y:
```c
if (raydirx == 0)
      deltadistx = 1e30;
else
      deltadistx = fabs(1 / raydirx);

if (raydiry == 0)
      deltadisty = 1e30;
else
      deltadisty = fabs(1 / raydiry);
```

1e30 is just “infinity but safe”, if a ray is purely vertical/horizontal, you don't want to divide by 0, so you give it a massive distance that will never win the X vs Y comparison, avoiding a crash.

### Next: Determine Step direction

If a ray goes left, you step -1 in X each time. If it goes right, +1. Same for Y.

And you compute the first side distance:
```c
sidedistx = (player.posx - mapx) * deltadistx;              // left
sidedistx = (mapx + 1.0 - player.posx) * deltadistx;       // right
```

This tells you how far from the player’s position to the next X grid line, starting the real DDA walk.

### 4. DDA Loop = March Until Hit

The function:
```c
while (!hit)
	hit = dda_step(engine, map_height);
```
Inside dda_step, we compare X vs Y sidedistance:
- smallest one wins (closest grid boundary)
- move mapx += stepx or mapy += stepy
- check bounds and tile contents
- if it's a '1' or 'D', that’s a hit → stop.
This gives you the exact tile that the ray collided with.

### 5. 3D Projection = Distance → Wall Height

To remove fish-eye distortion, we compute perpendicular distance, not raw ray length:
```c
perpdist = (mapx - posx + (1 - stepx)/2) / raydirx   // X wall
perpdist = (mapy - posy + (1 - stepy)/2) / raydiry   // Y wall
```
Now convert that to screen size:
```c
lineheight = SCREEN_HEIGHT / perpdist;
drawstart  = -lineheight/2 + SCREEN_HEIGHT/2;
drawend    =  lineheight/2 + SCREEN_HEIGHT/2;
```
So closer wall = taller line. Far wall = shorter line.
Then you draw a vertical textured strip there.
The depth buffer saves these distances so sprites/enemies know what is in front of them.

### 6. Colors = 32-bit packed ints

All colors are `32` bits: `0xRRGGBBAA`.

`<<24`, `<<16`, `<<8` shifts the r,g,b values into the 32-bit integer to form a final pixel color.

### 7.  Minimap = Same Math, Different Scale

Minimap rendering doesn’t invent new logic. It reuses world positions.

- Draw a filled circle background
- For each map tile, compute relative distance to player
- If it fits inside the circle radius, draw a 6×6 pixel block using the color from `get_tile_color`
- Player marker is also a `6×6` block in the circle center
- Circular border is drawn by sampling 0→360° using cos/sin.

So the minimap uses the same coordinate system, same unit circle math, same tile meaning, just scaled differently.

### 8. Movement = Direction or Plane Vector + Collision

Movement uses:
- dir vector for forward/back
- plane vector for strafing
Before confirming movement, collision is checked using check_collision:
- Map borders are enforced
- Tiles and door hitboxes block movement
- `isfinite` avoids NaN/infinite movement bugs
Pressing ESC prints your farewell message, then closes the window.

### 9. Exit = reverse of boot

After `mlx_loop` ends:

- cleanup textures

- cleanup enemy textures

- terminate MLX graphics instance
