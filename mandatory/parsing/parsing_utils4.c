/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:07:02 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/10/04 18:09:43 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

void	map_rectangular(char ***map_2d, int width)
{
	char	**new_map_2d;
	int		i;

	new_map_2d = *map_2d;
	i = -1;
	while (new_map_2d[++i])
		the_right_line(width, &new_map_2d[i]);
}

int	is_map_start(const char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '1' || line[i] == '0'
		|| line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'W' || line[i] == 'E')
		return (1);
	return (0);
}

int	handle_line(char *line, int *cp, t_data *data)
{
	if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)
		|| !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "NO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		extract_elements(line, cp, data);
	else if (is_empty_line(line))
		;
	else if (is_map_start(line))
		return (free(line),
			error_exit("Map found before all required elements"), 0);
	else
		return (free(line),
			error_exit("Invalid line before elements"), 0);
	return (1);
}

int	new_parsing(char *file, t_data *data)
{
	int		fd;
	int		height;
	int		width;
	char	*line;
	char	*map_line;

	init_data_elements(data);
	fd = openning_file(file);
	if (!parse_elements(fd, data))
		return (0);
	line = skip_empty_lines(fd);
	map_line = parse_map_lines(fd, line);
	if (!map_line)
		return (0);
	if (check_colors(data->f, &data->floor)
		|| check_colors(data->c, &data->ceiling))
		return (error_exit("Wrong colors"), 0);
	data->map = ft_my_split(map_line, '\n');
	getmap_dimentions(data->map, &height, &width);
	map_rectangular(&data->map, width);
	if (check_boundiries(data->map))
		return (error_exit("Map is not properly closed by walls"), 0);
	return (1);
}
