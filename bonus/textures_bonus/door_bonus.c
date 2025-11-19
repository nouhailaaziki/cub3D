/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:11:24 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/11/16 19:42:10 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

void	find_and_toggle_nearby_doors(t_engine *engine)
{
	int		front_x;
	int		front_y;

	front_x = (int)(engine->player.posx + engine->player.dirx);
	front_y = (int)(engine->player.posy + engine->player.diry);
	if (engine->data.map[front_y][front_x] == 'D')
		engine->data.map[front_y][front_x] = 'O';
}

void	handle_doors(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_SPACE)
		&& !engine->space_pressed)
	{
		engine->space_pressed = 1;
		find_and_toggle_nearby_doors(engine);
	}
	else if (!mlx_is_key_down(engine->mlx, MLX_KEY_SPACE))
		engine->space_pressed = 0;
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

void	auto_close_doors(t_engine *engine)
{
	int		x;
	int		y;
	double	dist_x;
	double	dist_y;
	double	distance;

	y = 0;
	while (engine->data.map[y])
	{
		x = 0;
		while (engine->data.map[y][x])
		{
			if (engine->data.map[y][x] == 'O')
			{
				dist_x = engine->player.posx - (x + 0.5);
				dist_y = engine->player.posy - (y + 0.5);
				distance = sqrt(dist_x * dist_x + dist_y * dist_y);
				if (distance > 2.0)
					engine->data.map[y][x] = 'D';
			}
			x++;
		}
		y++;
	}
}
