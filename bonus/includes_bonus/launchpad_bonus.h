/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpad_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:26:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/11/04 18:12:49 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHPAD_BONUS_H
# define LAUNCHPAD_BONUS_H

/*--------------------- System & Library Includes ---------------------*/
# include ".MLX42.h"           // MLX42 graphics library
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_EAST 2
# define TEX_WEST 3
# define TEX_DOOR 4
# define TEX_ENEMY 5

/*---------------------- Default Configuration ------------------------*/

/* Buffer size for get_next_line */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* Window width in pixels */
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1500
# endif

/* Window height in pixels */
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 900
# endif

/* Player movement speed */
# ifndef SPEED
#  define SPEED 0.05
# endif

# ifndef CELL_SIZE
#  define CELL_SIZE 20
# endif

/*----------------------------- Structures ----------------------------*/

typedef struct s_pos_data
{
	int		map_x;
	int		map_y;
	double	t_x;
	double	t_y;
}	t_pos_data;

typedef struct s_draw_data
{
	int	tex_x;
	int	tex_y;
	int	x;
	int	y;
}	t_draw_data;

/* Enemy animation data */
typedef struct s_enemy
{
	double		posx;
	double		posy;
	int			frame;
	double		frame_time;
	int			is_alive;
	double		distance_to_player;
}	t_enemy;

/* Sprite drawing data */
typedef struct s_sprite_data
{
	int	draw_start_x;
	int	draw_end_x;
	int	draw_start_y;
	int	draw_end_y;
	int	width;
	int	height;
	int	sprite_screen_x;
	int	v_move_screen;// Add this for vertical positioning
}	t_sprite_data;
/* RGB color representation */
typedef struct s_colors
{
	unsigned int	r;// Red component (0-255)
	unsigned int	g;// Green component (0-255)
	unsigned int	b;// Blue component (0-255)
}	t_colors;

/* Map and texture data */
typedef struct s_data
{
	char		*so;// South wall texture path
	char		*we;// West wall texture path
	char		*no;// North wall texture path
	char		*ea;// East wall texture path
	char		*f;// Floor color string
	char		*c;// Ceiling color string
	char		**map;// 2D map layout
	t_colors	floor;// Parsed floor RGB color
	t_colors	ceiling;// Parsed ceiling RGB color
}	t_data;

/* Texture coordinate data */
typedef struct s_tex_data
{
	int	tex_x;// Horizontal coordinate in the texture
	int	tex_y;// Vertical coordinate in the texture
}	t_tex_data;

/* Player position and viewing direction */
typedef struct s_player
{
	double	posx;// Player X position
	double	posy;// Player Y position
	double	dirx;// Direction vector X
	double	diry;// Direction vector Y
	double	planex;// Camera plane X
	double	planey;// Camera plane Y
}	t_player;

/* Main game engine struct */
typedef struct s_engine
{
	mlx_texture_t	*so;// South wall texture path
	mlx_texture_t	*we;// West wall texture path
	mlx_texture_t	*no;// North wall texture path
	mlx_texture_t	*ea;// East wall texture path
	mlx_texture_t	*current_tex;// pointer to which texture 
								//we're currently using
	int				mapx;// Current map X coordinate
	int				mapy;// Current map Y coordinate
	int				stepx;// Step direction X for DDA
	int				stepy;// Step direction Y for DDA
	int				side;// Side of the wall hit (0=X, 1=Y)
	int				lineheight;// Height of the wall slice
	int				drawstart;// Start Y pixel for drawing wall
	int				drawend;// End Y pixel for drawing wall
	short			mouse;
	int32_t			mousex;
	int32_t			mousey;
	int32_t			prev_mousex;
	double			camerax;// Camera plane X for raycasting
	double			raydirx;// Ray direction X
	double			raydiry;// Ray direction Y
	double			deltadistx;// Distance to next X side
	double			deltadisty;// Distance to next Y side
	double			sidedistx;// Side distance X
	double			sidedisty;// Side distance Y
	double			perpwalldist;// Perpendicular distance to wall
	double			wall_x;// the exact position where the ray hit the wall
	double			tex_pos;//Tracks the vertical position in the texture as we 
							//draw the wall slice
	mlx_t			*mlx;// MLX window instance
	mlx_image_t		*image;// MLX image buffer
	t_data			data;// Map and texture data
	t_player		player;// Player info
	mlx_texture_t	*door;
	mlx_texture_t	*enemy_frames[6];// Array for 6 animation frames
	double			animation_time;// Global animation timer
	double			*buffer;
}	t_engine;

/*----------------------------- Parsing --------------------------------*/
int		init_data_elements(t_data *data);
int		parse_elements(int fd, t_data *data);
char	*skip_empty_lines(int fd);
int		is_empty_line(char *line);
char	*parse_map_lines(int fd, char *line);
int		new_parsing(char *file, t_data *data);
void	getmap_dimentions(char **map, int *h, int *w);
void	extract_elements(char *line, int *cp, t_data *data);
int		is_map_start(const char *line);
int		handle_line(char *line, int *cp, t_data *data);
int		validate_map_char(char *line);
void	map_rectangular(char ***map_2d, int width);
void	the_right_line(int width, char **s);

/*----------------------------- File Utils -----------------------------*/
int		openning_file(char *av);
int		validate_args(int argc, char **argv);
int		validate_file_extension(char *filename);
int		file_exists(const char *filename);

/*----------------------------- GNL & Libft ----------------------------*/
char	*get_next_line(int fd);
char	**ft_split(char *s, char c);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *s1);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_isdigit(int c);
void	cleanup_textures(t_engine *engine);
char	**ft_my_split(char *s, char c);

/*---------------------------- Color Checks ----------------------------*/
int		ft_is_valid_color_value(char *s);
int		check_colors(char *line, t_colors *color);
char	*get_data(char *line, char c);

/*----------------------------- Map Checks -----------------------------*/
int		check_zero(char c);
int		check_boundiries(char **map);
int		iszeroplayerdoor(char c);

/*----------------------------- Exit -----------------------------------*/
void	error_exit(char *message);

/*------------------------ Raycasting Functions ------------------------*/
int		master(t_engine *engine);
void	render_horizon(void *param);
void	setup_ray(t_engine *engine, int x);
void	set_ray_deltas(t_engine *engine);
void	set_initial_sides(t_engine *engine);
void	perform_dda(t_engine *engine);
void	calculate_wall_projection(t_engine *engine);
void	init_data(t_engine *engine);
void	raycast_frame(void *param);
void	rotate_via_keys(void *param);
void	rotate_via_mouse(void *param);
void	wanderer_controls(void *param);
void	farewell_wanderer(void *param);
void	render_minimap(t_engine *engine);
int		get_tile_color(char c);

/*---------------------------- Textures --------------------------------*/
void	calculate_texture_data(t_engine *e);
void	draw_textured_pixel(t_engine *engine, int x, int y,
			mlx_texture_t *tex);
void	draw_textured_line(t_engine *e, int x, int t);
int		get_texture_index(t_engine *engine);
int		load_textures(t_engine *engine);

/*---------------------- Garbage Collector -----------------------------*/
void	free_all(void *p, int flag);
void	free_and_exit(size_t i);
void	*ft_alloc(size_t i);

/*------------------------------ Doors ---------------------------------*/
void	toggle_door(t_engine *engine, int x, int y);
void	handle_doors(void *param);

/*---------------------------- Enemy Functions ----------------------------*/
void	render_all_enemies(t_engine *engine);
void	cleanup_enemy_textures(t_engine *engine);
void	update_enemies_hook(void *param);
void	calculate_enemy_screen_position(t_engine *engine, t_pos_data *pos);
void	calculate_enemy_sprite_data(double t_x, double t_y, t_sprite_data *sp);
void	check_game_over(t_engine *engine);
int		load_enemy_textures(t_engine *engine);
#endif
