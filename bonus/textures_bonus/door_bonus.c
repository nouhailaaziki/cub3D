/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:11:24 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/11/04 17:47:34 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

void	toggle_door(t_engine *engine, int x, int y)
{
	if (engine->data.map[y][x] == 'D')
		engine->data.map[y][x] = 'O';
	else if (engine->data.map[y][x] == 'O')
		engine->data.map[y][x] = 'D';
}

void	auto_open_close_doors(t_engine *engine)
{
	int		x;
	int		y;
	double	dist_x;
	double	dist_y;
	double	distance;

	y = -1;
	while (engine->data.map[++y])
	{
		x = -1;
		while (engine->data.map[y][++x])
		{
			if (engine->data.map[y][x] == 'D' || engine->data.map[y][x] == 'O')
			{
				dist_x = engine->player.posx - (x + 0.5);
				dist_y = engine->player.posy - (y + 0.5);
				distance = sqrt(dist_x * dist_x + dist_y * dist_y);
				if (engine->data.map[y][x] == 'D' && distance < 1.5)
					engine->data.map[y][x] = 'O';
				else if (engine->data.map[y][x] == 'O' && distance > 1.5)
					engine->data.map[y][x] = 'D';
			}
		}
	}
}

void	handle_doors(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	auto_open_close_doors(engine);
}

void	check_game_over(t_engine *engine)
{
	int	map_x;
	int	map_y;

	map_x = (int)engine->player.posx;
	map_y = (int)engine->player.posy;
	if (engine->data.map[map_y][map_x] == 'M')
	{
		ft_putstr_fd("GAME OVER! An enemy caught you!\n", 1);
		mlx_close_window(engine->mlx);
	}
}
