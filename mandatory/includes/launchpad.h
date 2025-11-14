/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpad.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:26:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/11/14 12:35:27 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHPAD_H
# define LAUNCHPAD_H

/*--------------------- System & Library Includes ---------------------*/
# include ".MLX42.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/*---------------------- Default Configuration ------------------------*/
# define TEX_NORTH 0
# define TEX_SOUTH 1  
# define TEX_EAST 2
# define TEX_WEST 3
# define BUFFER_SIZE 1
# define SCREEN_WIDTH 1500
# define SCREEN_HEIGHT 900
# define SPEED 0.05
# define CELL_SIZE 20

/*----------------------------- Structures ----------------------------*/

/* RGB color representation */
typedef struct s_colors
{
	unsigned int	r;/* Red component (0-255) */
	unsigned int	g;/* Green component (0-255) */
	unsigned int	b;/* Blue component (0-255) */
}	t_colors;

/* Map and texture data */
typedef struct s_data
{
	char		*so;/* South wall texture path */
	char		*we;/* West wall texture path */
	char		*no;/* North wall texture path */
	char		*ea;/* East wall texture path */
	char		*f;/* Floor color string */
	char		*c;/* Ceiling color string */
	char		**map;/* 2D map layout */
	t_colors	floor;/* Parsed floor RGB color */
	t_colors	ceiling;/* Parsed ceiling RGB color */
}	t_data;

/* Player position and viewing direction */
typedef struct s_player
{
	double	posx;/* Player X position in the map */
	double	posy;/* Player Y position in the map */
	double	dirx;/* Direction vector X */
	double	diry;/* Direction vector Y */
	double	planex;/* Camera plane X (perp. to dir) */
	double	planey;/* Camera plane Y */
}	t_player;

/* texture coordinates data */
typedef struct s_tex_data
{
	int	tex_x;/* Horizontal coord in texture (0..width-1) */
	int	tex_y;/* Vertical coord in texture (0..height-1) */
}	t_tex_data;

/* Main game engine struct */
typedef struct s_engine
{
	int				mapx;/* Current map X coord */
	int				mapy;/* Current map Y coord */
	int				stepx;/* Step direction X for DDA */
	int				stepy;/* Step direction Y for DDA */
	int				side;/* Side of wall hit (0=X, 1=Y) */
	int				lineheight;/* Height of the wall slice */
	int				drawstart;/* Start Y pixel for drawing wall */
	int				drawend;/* End Y pixel for drawing wall */
	double			camerax;/* Camera plane X for raycasting */
	double			raydirx;/* Ray direction X */
	double			raydiry;/* Ray direction Y */
	double			deltadistx;/* Distance to next X side */
	double			deltadisty;/* Distance to next Y side */
	double			sidedistx;/* Side distance X */
	double			sidedisty;/* Side distance Y */
	double			perpwalldist;/* Perp. distance to wall */
	double			wall_x;/* Exact position where ray hit wall */
	double			tex_pos;/* Vertical pos in texture while drawing */
	mlx_t			*mlx;/* MLX window instance */
	t_data			data;/* Map and texture data */
	t_player		player;/* Player info */
	mlx_image_t		*image;/* MLX image buffer */
	mlx_texture_t	*so;/* South wall texture */
	mlx_texture_t	*we;/* West wall texture */
	mlx_texture_t	*no;/* North wall texture */
	mlx_texture_t	*ea;/* East wall texture */
	mlx_texture_t	*current_tex;/* Pointer to current texture in use */
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

/*----------------------------- Exit ----------------------------------*/
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
void	wanderer_controls(void *param);
void	farewell_wanderer(void *param);
void	get_map_dimensions(t_engine *e, int *h, int *w);

/*---------------------------- Textures --------------------------------*/
int		load_textures(t_engine *engine);
int		get_texture_index(t_engine *engine);
void	calculate_texture_data(t_engine *e);
void	draw_textured_line(t_engine *e, int x, int t);
void	draw_textured_pixel(t_engine *engine,
			int x, int y, mlx_texture_t *tex);

/*------------------------- garbage_collector --------------------------*/
void	free_all(void *p, int flag);
void	free_and_exit(size_t i);
void	*ft_alloc(size_t i);
void	close_fd(void);

#endif