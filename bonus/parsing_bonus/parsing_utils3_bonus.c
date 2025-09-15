/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:09:51 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/09/15 15:10:18 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	is_invalid(char **map, int i, int j, int h)
{
	int	len_curr;
	int	len_next;
	int	len_prev;

	len_curr = ft_strlen(map[i]);
	len_next = 0;
	if (i + 1 < h)
		len_next = ft_strlen(map[i + 1]);
	len_prev = 0;
	if (i - 1 >= 0)
		len_prev = ft_strlen(map[i - 1]);
	if (j + 1 >= len_curr || j - 1 < 0)
		return (1);
	if (i + 1 >= h || j >= len_next)
		return (1);
	if (i - 1 < 0 || j >= len_prev)
		return (1);
	return (0);
}

int	check_boundiries(char **map)
{
	int	i;
	int	j;
	int	height;

	height = 0;
	while (map[height])
		height++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (is_invalid(map, i, j, height))
					return (1);
			}
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
