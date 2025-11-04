/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:40:03 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/11/03 18:41:43 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	validate_map_char(char *line)
{
	int	i;
	int	cp;

	i = 0;
	cp = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n'
			&& line[i] != '0' && line[i] != '1'
			&& line[i] != 'S' && line[i] != 'N'
			&& line[i] != 'W' && line[i] != 'E'
			&& line[i] != 'D' && line[i] != 'M'
			&& line[i] != '\r')
			return (error_exit("Wrong char in the map"), 1);
		if (line[i] == 'S' || line[i] == 'N'
			|| line[i] == 'W' || line[i] == 'E')
			cp++;
		i++;
	}
	if (cp != 1)
		return (error_exit("It should be just 1 player"), 1);
	return (0);
}

int	ft_is_valid_color_value(char *s)
{
	int	val;
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	if (i < 1 || i > 3)
		return (0);
	val = ft_atoi(s);
	if (val < 0 || val > 255)
		return (0);
	return (1);
}

int	validate_comma_format(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == ',' || line[ft_strlen(line) - 1] == ',')
		return (0);
	while (line[i])
	{
		if (line[i] == ',' && (line[i + 1] == ',' || !line[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	check_colors(char *line, t_colors *color)
{
	char	**parts;
	int		i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && (line[i] == '\n' || line[i] == '\r'))
		line[i--] = '\0';
	if (!validate_comma_format(line))
		return (1);
	parts = ft_my_split(line, ',');
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
		return (1);
	if (!ft_is_valid_color_value(parts[0]) || !ft_is_valid_color_value(parts[1])
		|| !ft_is_valid_color_value(parts[2]))
		return (1);
	color->r = ft_atoi(parts[0]);
	color->g = ft_atoi(parts[1]);
	color->b = ft_atoi(parts[2]);
	return (0);
}

int	check_zero(char c)
{
	if (c == ' ' || c == '\0')
		return (1);
	return (0);
}
