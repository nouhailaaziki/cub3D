/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:47:46 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/09/15 14:47:46 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

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
			return (0);
		if (!handle_line(line, &cp, data))
			return (0);
		if (cp == 6)
			break ;
	}
	if (!data->so || !*data->so || !data->we || !*data->we
		|| !data->no || !*data->no || !data->ea || !*data->ea
		|| !data->f || !*data->f || !data->c || !*data->c)
		return (error_exit("Something wrong in textures/colors"), 0);
	return (1);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '\n' && line[i] != '\r')
			return (0);
		i++;
	}
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
		if (!is_empty_line(line))
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
		if (is_empty_line(line))
			return (error_exit("New lines in map"), NULL);
		map_line = ft_strjoin(map_line, line);
		line = get_next_line(fd);
	}
	if (validate_map_char(map_line))
		return (NULL);
	return (map_line);
}
