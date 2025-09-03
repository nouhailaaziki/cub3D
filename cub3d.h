/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:06:39 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/09/03 17:59:27 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif



typedef struct s_colors
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
} t_colors;


typedef struct s_data
{
    char *so;
    char *we;
    char *no;
    char *ea;
    char *f;
    char *c;
    char **map;
    t_colors floor;
    t_colors ceileing;
} t_data;



//////parsing
int     new_parsing(char *file, t_data *data);
void getmap_dimentions(char **map, int *h, int *w);

///////////////split
char	**ft_split(char *s, char c);

//////////////get_next_line
int	    validate_elements(t_data *data);
char	*get_next_line(int fd);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup( char *s1);
// /////utils2
void	free_array(char **array);
void	free_textures(t_data *data);
void	free_cub3d(t_data *data);
int     openning_file(char *av);


// ////////utils1
void    error_exit(char *message);
int	    ft_atoi(const char *str);
int     ft_strcmp(const char *s1, const char *s2);
void    ft_putstr_fd(char *s, int fd);
int     ft_strncmp(char *s1, char *s2, size_t n);


// /////////parsing_utils1
int	validate_args(int argc, char **argv);
int	validate_file_extension(char *filename);
int	file_exists(const char *filename);
char *get_data(char *line, char c);
void extract_elements(char *line, int *cp, t_data *data);


////parsing_utils2
int null_elements(char *el);
int check_wrong_el(char *line);
int check_colors(char *line, t_colors *color);
int check_zero(char c);
int check_boundiries(char **map);

#endif

