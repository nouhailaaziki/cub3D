/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:08:51 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/09/15 16:09:07 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

void	fix_map(char ***map_2d, int width)
{
	char	**new_map_2d;
	int		i;

	new_map_2d = *map_2d;
	i = -1;
	while (new_map_2d[++i])
		the_right_line(width, &new_map_2d[i]);
}
