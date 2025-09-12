/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/12 16:31:16 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

void	set_player_direction(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dirx = cos(3 * M_PI / 2);
		player->diry = sin(3 * M_PI / 2);
	}
	else if (c == 'S')
	{
		player->dirx = cos(M_PI / 2);
		player->diry = sin(M_PI / 2);
	}
	else if (c == 'E')
	{
		player->dirx = cos(0);
		player->diry = sin(0);
	}
	else if (c == 'W')
	{
		player->dirx = cos(M_PI);
		player->diry = sin(M_PI);
	}
	player->planex = - player->diry * 0.66;
	player->planey = player->dirx * 0.66;
}

void	init_data(t_engine *engine)
{
	int		i;
	int		j;
	char	**map;

	1 && (i = 0, map = engine->data.map);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				engine->player.posy = i + 0.5;
				engine->player.posx = j + 0.5;
				set_player_direction(&engine->player, map[i][j]);
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	setup_ray(t_engine *engine, int x)
{
	engine->camerax = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
	engine->raydirx = engine->player.dirx + \
	engine->player.planex * engine->camerax;
	engine->raydiry = engine->player.diry + \
	engine->player.planey * engine->camerax;
}
