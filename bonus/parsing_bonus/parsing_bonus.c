/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:17:15 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/09/15 16:17:15 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	init_data_elements(t_data *data)
{
	data->so = NULL;
	data->we = NULL;
	data->no = NULL;
	data->ea = NULL;
	data->f = NULL;
	data->c = NULL;
	return (0);
}

int	parse_elements(int fd, t_data *data)
{
	char	*line;
	int		cp;

	cp = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (error_exit(
					"Missing required elements (NO, SO, WE, EA, F, C)"), 0);
		if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)
			|| !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "NO", 2)
			|| !ft_strncmp(line, "WE", 2)
			|| !ft_strncmp(line, "EA", 2))
			extract_elements(line, &cp, data);
		free(line);
		if (cp == 6)
			break ;
	}
	if (null_elements(data->so) || null_elements(data->we)
		|| null_elements(data->no) || null_elements(data->ea)
		|| null_elements(data->f)
		|| null_elements(data->c))
		return (error_exit("Duplicate in textures/colors"), 0);
	return (1);
}

char	*skip_empty_lines(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strcmp(line, "\n"))
			break ;
	}
	if (!line)
		return (error_exit("No map"), NULL);
	return (line);
}

char	*parse_map_lines(int fd, char *line)
{
	char	*map_line;

	map_line = NULL;
	while (line)
	{
		if (!ft_strcmp(line, "\n"))
			return (error_exit("New lines in map"), NULL);
		map_line = ft_strjoin(map_line, line);
		line = get_next_line(fd);
	}
	if (check_wrong_el(map_line))
		return (error_exit("Something wrong in the map"), NULL);
	return (map_line);
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
	data->map = ft_split(map_line, '\n');
	if (check_boundiries(data->map))
		return (error_exit("Map is not properly closed by walls"), 0);
	getmap_dimentions(data->map, &height, &width);
	fix_map(&data->map, width);
	return (1);
}
