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
See the diagram below for a visual explanation of player initialization and camera orientation.
![Player Start & Camera Orientation](tldraw_diagrams/init_data.png)

### 2. mlx_load_png()

- It’s a function in MLX42 used to load a PNG file from disk.

- It doesn’t create a drawable image directly for the window — instead, it loads a texture (a data structure that holds the raw pixel data + meta info).

What it Returns?

- Returns a pointer to a mlx_texture_t (texture object), or NULL if loading fails.

- The texture contains:

  - Width and height of the image

  - Bytes per pixel (how many bytes make up each pixel)

  - A buffer of the pixel data

This is described in the MLX42 “Textures” documentation. 
GitHub Wiki

Why Use Textures vs Images

- Texture: just holds pixel data in memory, but does not know about windows or rendering directly.

- Image: used for rendering to a window. You convert a texture into an image (for example with mlx_texture_to_image) when you want to display it on screen. 
GitHub Wiki

- This design separates loading (texture) from displaying (image), which is efficient.

### 3. mlx_set_setting(MLX_STRETCH_IMAGE, true)

- Purpose: Configures how MiniLibX handles image scaling.

- MLX_STRETCH_IMAGE: Tells MLX to stretch images to fit the drawing area instead of cropping or tiling them.

- Why it matters: Prevents textures from looking wrong or distorted when displayed on the screen.

- Example: If your wall texture is smaller than a wall on the screen, it will be stretched to cover it.

### 4. mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Title", false)

- Purpose: Initializes the MLX graphics library and creates a window.

- Arguments:

  1. SCREEN_WIDTH – width of the window.

  2. SCREEN_HEIGHT – height of the window.

  3. "Title" – text shown on the window’s title bar.

  4. false – whether the window should be fullscreen (true → fullscreen). In MLX42, that last parameter in mlx_init(width, height, title, fullscreen) does NOT create a real fullscreen window, even if you pass true. That argument is misleading — it only works on some systems and not the way you expect.

- Return value:

  - A pointer to the MLX instance (stored in engine->mlx in my code).

  - NULL → failure to create the window.

- Why it’s needed: MLX provides all the graphics functions for drawing, handling images, and creating windows. You can’t draw anything without it.

### 5. mlx_strerror(mlx_errno)

Purpose: Converts an MLX error code into a human-readable message.

mlx_errno: A global variable that MLX sets when an error occurs.

Example: If creating a window fails, mlx_strerror(mlx_errno) might return "Failed to create window".

Why it’s useful: Helps you understand why something went wrong during initialization.

### 6. mlx_new_image(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT)

Purpose: Creates an offscreen image buffer where the game will draw everything before showing it on the screen.

Why use an offscreen buffer:

Prevents flickering.

Lets you draw the entire frame at once before displaying it.

Arguments: Same as the window size.

Return value: A pointer to the image; NULL if it fails.

### 7. cleanup_textures(engine)

Purpose: Frees all textures previously loaded into memory.

Why it’s important:

Prevents memory leaks if something goes wrong.

Usually called if loading textures fails or if the program exits unexpectedly.
