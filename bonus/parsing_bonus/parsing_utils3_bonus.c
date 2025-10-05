/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:09:51 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/10/04 20:34:07 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	iszeroplayerdoor(char c)
{
	return (c == '0' || c == 'N' || c == 'W' || c == 'E' || c == 'S'
		|| c == 'D');
}

int	check_boundiries(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (iszeroplayerdoor(map[i][j]) && (i == 0 || j == 0
			|| !map[i][j + 1] || !map[i + 1] || check_zero(map[i][j + 1])
			|| check_zero(map[i][j - 1]) || check_zero(map[i + 1][j])
			|| check_zero(map[i - 1][j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	getmap_dimentions(char **map, int *h, int *w)
{
	int	new_width;

	*h = 0;
	*w = 0;
	while (map[*h])
	{
		new_width = ft_strlen(map[*h]);
		if (new_width > *w)
			*w = new_width;
		(*h)++;
	}
}

void	ft_bspace(int width, char **p)
{
	int	i;

	*p = malloc(width + 1);
	i = 0;
	while (i < width)
		p[0][i++] = ' ';
	p[0][i] = '\0';
}

void	the_right_line(int width, char **s)
{
	int		i;
	int		j;
	char	*p;

	ft_bspace(width, &p);
	i = 0;
	j = 0;
	while (i < width)
	{
		if (i < ft_strlen(*s))
			p[j++] = (*s)[i];
		i++;
	}
	free(*s);
	*s = p;
}
