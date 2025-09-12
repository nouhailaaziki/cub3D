/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpad.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:26:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/12 17:35:38 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHPAD_H
# define LAUNCHPAD_H

/*--------------------- System & Library Includes ---------------------*/
# include ".MLX42.h"           // MLX42 graphics library
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

/*---------------------- Default Configuration ------------------------*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1        // Buffer size for get_next_line
# endif

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1500    // Window width
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 900    // Window height
# endif

# ifndef SPEED
#  define SPEED 0.05
# endif
/*----------------------------- Structures ----------------------------*/

/* RGB color representation */
typedef struct s_colors
{
	unsigned int	r;         // Red component (0-255)
	unsigned int	g;         // Green component (0-255)
	unsigned int	b;         // Blue component (0-255)
}	t_colors;

/* Map and texture data */
typedef struct s_data
{
	char		*so;           // South wall texture path
	char		*we;           // West wall texture path
	char		*no;           // North wall texture path
	char		*ea;           // East wall texture path
	char		*f;            // Floor color string
	char		*c;            // Ceiling color string
	char		**map;         // 2D map layout
	t_colors	floor;         // Parsed floor RGB color
	t_colors	ceiling;       // Parsed ceiling RGB color
}	t_data;

/* Player position and viewing direction */
typedef struct s_player
{
	double	posx;              // Player X position in the map
	double	posy;              // Player Y position in the map
	double	dirx;              // Direction vector X
	double	diry;              // Direction vector Y
	double	planex;            // Camera plane X (perpendicular to dir)
	double	planey;            // Camera plane Y
}	t_player;

/* Main game engine struct */
typedef struct s_engine
{
	int			mapx;          // Current map X coordinate
	int			mapy;          // Current map Y coordinate
	int			stepx;         // Step direction X for DDA
	int			stepy;         // Step direction Y for DDA
	int			side;          // Side of the wall hit (0=X, 1=Y)
	int			lineheight;    // Height of the wall slice
	int			drawstart;     // Start Y pixel for drawing wall
	int			drawend;       // End Y pixel for drawing wall
	double		camerax;       // Camera plane X for raycasting
	double		raydirx;       // Ray direction X
	double		raydiry;       // Ray direction Y
	double		deltadistx;    // Distance to next X side
	double		deltadisty;    // Distance to next Y side
	double		sidedistx;     // Side distance X
	double		sidedisty;     // Side distance Y
	double		perpwalldist;  // Perpendicular distance to wall
	mlx_t		*mlx;          // MLX window instance
	mlx_image_t	*image;        // MLX image buffer
	t_data		data;          // Map and texture data
	t_player	player;        // Player info
}	t_engine;

/*----------------------------- Parsing --------------------------------*/
int		new_parsing(char *file, t_data *data);
void	getmap_dimentions(char **map, int *h, int *w);
void	extract_elements(char *line, int *cp, t_data *data);
int		null_elements(char *el);
int		check_wrong_el(char *line);

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

/*---------------------------- Color Checks ----------------------------*/
int		check_colors(char *line, t_colors *color);
char	*get_data(char *line, char c);

/*----------------------------- Map Checks -----------------------------*/
int		check_zero(char c);
int		check_boundiries(char **map);

/*----------------------------- Free & Exit ----------------------------*/
void	free_array(char **array);
void	free_textures(t_data *data);
void	free_cub3d(t_data *data);
void	error_exit(char *message);

/*------------------------ Raycasting Functions ------------------------*/
int		master(t_engine *engine);
void	render_horizon(t_engine *engine);
void	setup_ray(t_engine *engine, int x);
void	set_ray_deltas(t_engine *engine);
void	set_initial_sides(t_engine *engine);
void	perform_dda(t_engine *engine);
void	calculate_wall_projection(t_engine *engine);
void	init_data(t_engine *engine);
void	draw_vertical_line(t_engine *engine, int x, uint32_t color);

#endif