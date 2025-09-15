/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:07:02 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/09/15 16:07:18 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

void	fix_map(char ***map_2d, int width)
{
	char	**new_map_2d;
	int		i;

	new_map_2d = *map_2d;
	i = -1;
	while (new_map_2d[++i])
		the_right_line(width, &new_map_2d[i]);
}
