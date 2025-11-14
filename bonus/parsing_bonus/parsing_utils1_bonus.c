/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:17:24 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/11/13 16:03:28 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	validate_args(int argc, char **argv)
{
	if (argc != 2)
	{
		error_exit("Invalid number of arguments");
		return (1);
	}
	if (validate_file_extension(argv[1]) != 0)
		return (1);
	if (file_exists(argv[1]) != 0)
		return (1);
	return (0);
}

int	validate_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		error_exit("Wrong file extension");
		return (1);
	}
	return (0);
}

int	file_exists(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		error_exit("Cannot open file");
		return (1);
	}
	return (0);
}

char	*get_data(char *line, char c)
{
	int	i;
	int	j;

	i = 0;
	if (c == 'F' || c == 'C')
		i++;
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
		i += 2;
	while (line[i] == ' ')
		i++;
	j = ft_strlen(line) - 1;
	while (j >= i && (line[j] == '\n' || line[j] == '\r'))
		line[j--] = '\0';
	return (ft_strdup(&line[i]));
}

void	extract_elements(char *line, int *cp, t_data *data)
{
	if (!ft_strncmp(line, "F", 1))
		data->f = get_data(line, 'F');
	if (!ft_strncmp(line, "C", 1))
		data->c = get_data(line, 'C');
	if (!ft_strncmp(line, "SO", 2))
		data->so = get_data(line, 'S');
	if (!ft_strncmp(line, "NO", 2))
		data->no = get_data(line, 'N');
	if (!ft_strncmp(line, "WE", 2))
		data->we = get_data(line, 'W');
	if (!ft_strncmp(line, "EA", 2))
		data->ea = get_data(line, 'E');
	(*cp)++;
}
