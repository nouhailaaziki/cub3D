/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:11:24 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/10/23 17:56:15 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	is_player_near_door(t_engine *engine, int door_x, int door_y)
{
	double	dist_x;
	double	dist_y;
	double	distance;

	dist_x = engine->player.posx - (door_x + 0.5);
	dist_y = engine->player.posy - (door_y + 0.5);
	distance = sqrt(dist_x * dist_x + dist_y * dist_y);
	if (distance < 1)
		return (1);
	return (0);
}

void	toggle_door(t_engine *engine, int x, int y)
{
	if (engine->data.map[y][x] == 'D')
		engine->data.map[y][x] = 'O';
	else if (engine->data.map[y][x] == 'O')
		engine->data.map[y][x] = 'D';
}

void	find_and_toggle_nearby_doors(t_engine *engine)
{
	int	x;
	int	y;

	y = 0;
	while (engine->data.map[y])
	{
		x = 0;
		while (engine->data.map[y][x])
		{
			if ((engine->data.map[y][x] == 'D' || engine->data.map[y][x] == 'O')
				&& is_player_near_door(engine, x, y))
			{
				toggle_door(engine, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
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
