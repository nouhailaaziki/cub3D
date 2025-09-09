/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpad.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:26:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/09 09:50:56 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHPAD_H
# define LAUNCHPAD_H

/*--------------------- System & Library Includes ---------------------*/
# include ".MLX42.h"
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

/*---------------------- Default Configuration ------------------------*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

// # ifndef M_PI
// #  define M_PI 3.14159265358979323846
// # endif

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1500
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 900
# endif

/*----------------------------- Structures ----------------------------*/

/* RGB color representation */
typedef struct s_colors
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_colors;

/* Map & texture data */
typedef struct s_data
{
	char		*so;        // South texture
	char		*we;        // West texture
	char		*no;        // North texture
	char		*ea;        // East texture
	char		*f;         // Floor color string
	char		*c;         // Ceiling color string
	char		**map;      // 2D map layout
	t_colors	floor;      // Parsed floor color
	t_colors	ceiling;    // Parsed ceiling color
}	t_data;

typedef struct s_player {
    double  posX;       // player position X
    double  posY;       // player position Y
    double  dirX;       // direction vector X
    double  dirY;       // direction vector Y
    double  planeX;     // camera plane X (perpendicular to dir)
    double  planeY;     // camera plane Y
}   t_player;

/* Main struct holding all important parameters of the game */
typedef struct s_engine
{
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_data		data;
	t_player	player;
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


int	master(t_engine *engine);
#endif